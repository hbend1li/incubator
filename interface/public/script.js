var gateway = `ws://${window.location.hostname}/ws`;
var websocket;
var GraphLabel = [], GraphTemperatureD = [], GraphHumidityD = [], GraphTemperatureG = [], GraphHumidityG = [];
var GraphSPIFFS_t = 0, GraphSPIFFS_u = 0, GraphSPIFFS_f = 0;
window.addEventListener('load', onLoad);

var chart_d = new Chart(document.getElementById('myChartCanvasD'), {
    type: 'line',
    data: {
        labels: GraphLabel,
        datasets: [{
            label: 'Temperature',
            data: GraphTemperatureD,
            borderWidth: 1,
            cubicInterpolationMode: 'monotone',
            borderColor: '#ffb700',
            backgroundColor: '#ffb700',
            pointStyle: false,
        }, {
            label: 'Humidity',
            data: GraphHumidityD,
            borderWidth: 1,
            cubicInterpolationMode: 'monotone',
            borderColor: '#00add6',
            backgroundColor: '#00add6',
            pointStyle: false,
        }]
    },
    options: {
        scales: {
            y: {
                beginAtZero: false
            }
        }
    }
});

var chart_g = new Chart(document.getElementById('myChartCanvasG'), {
    type: 'line',
    data: {
        labels: GraphLabel,
        datasets: [{
            label: 'Temperature',
            data: GraphTemperatureG,
            borderWidth: 1,
            cubicInterpolationMode: 'monotone',
            borderColor: '#ffb700',
            backgroundColor: '#ffb700',
            pointStyle: false,
        }, {
            label: 'Humidity',
            data: GraphHumidityG,
            borderWidth: 1,
            cubicInterpolationMode: 'monotone',
            borderColor: '#00add6',
            backgroundColor: '#00add6',
            pointStyle: false,
        }]
    },
    options: {
        scales: {
            y: {
                beginAtZero: false
            }
        }
    }
});

var diskspace_js = new Chart(document.getElementById('diskspace'), {
    type: 'doughnut',
    data: {
        labels: ['Used', 'Free'],
        datasets: [{
            label: 'Disk',
            data: [GraphSPIFFS_u, GraphSPIFFS_f],
            borderWidth: 1,
            cubicInterpolationMode: 'monotone',
            pointStyle: false,
        }]
    }
});

function onLoad(event) {
    initWebSocket();
    reloadGraph();
}

function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen = onOpen;
    websocket.onclose = onClose;
    websocket.onmessage = onMessage;
}

function onOpen(event) {
    console.log('Connection opened');
    get('Status');
}

function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
}

function onMessage(event) {
    var myObj = JSON.parse(event.data);
    console.log(myObj);

    // Temperature / Humidity
    if (myObj.TemperatureD) document.getElementById("TemperatureD").innerHTML = Number(myObj.TemperatureD).toFixed(1);
    if (myObj.HumidityD) document.getElementById("HumidityD").innerHTML = Number(myObj.HumidityD).toFixed(0);
    if (myObj.TemperatureG) document.getElementById("TemperatureG").innerHTML = Number(myObj.TemperatureG).toFixed(1);
    if (myObj.HumidityG) document.getElementById("HumidityG").innerHTML = Number(myObj.HumidityG).toFixed(0);
    // Thermosta
    if (myObj.tL) document.getElementById("tL").value = Number(myObj.tL).toFixed(1);
    if (myObj.tH) document.getElementById("tH").value = Number(myObj.tH).toFixed(1);
    if (myObj.hL) document.getElementById("hL").value = Number(myObj.hL).toFixed(0);
    if (myObj.hH) document.getElementById("hH").value = Number(myObj.hH).toFixed(0);
    // Relay 1-4

    if (myObj.r1 === true || myObj.r1 === false) {
        document.getElementById("r1s").checked = myObj.r1;
        document.getElementById("r1span").innerHTML = myObj.r1 ? 'ON' : 'OFF';
    }
    if (myObj.r2 === true || myObj.r2 === false) {
        document.getElementById("r2s").checked = myObj.r2;
        document.getElementById("r2span").innerHTML = myObj.r2 ? 'ON' : 'OFF';
    }
    if (myObj.r3 === true || myObj.r3 === false) {
        document.getElementById("r3s").checked = myObj.r3;
        document.getElementById("r3span").innerHTML = myObj.r3 ? 'ON' : 'OFF';
    }
    if (myObj.r4 === true || myObj.r4 === false) {
        document.getElementById("r4s").checked = myObj.r4;
        document.getElementById("r4span").innerHTML = myObj.r4 ? 'ON' : 'OFF';
    }
    // WIFI
    if (myObj.wifi_ssid) document.getElementById("wifi_ssid").value = myObj.wifi_ssid;
    if (myObj.wifi_key) document.getElementById("wifi_key").value = myObj.wifi_key;
    if (myObj.wifi_ap_mode) document.getElementById("wifi_ap_mode").checked = myObj.wifi_ap_mode;
    // MQTT
    if (myObj.mqtt_host) document.getElementById("mqtt_host").value = myObj.mqtt_host;
    if (myObj.mqtt_port) document.getElementById("mqtt_port").value = myObj.mqtt_port;
    //if (myObj.mqtt_client_id) document.getElementById("mqtt_client_id").value = myObj.mqtt_client_id;
    if (myObj.mqtt_username) document.getElementById("mqtt_username").value = myObj.mqtt_username;
    if (myObj.mqtt_password) document.getElementById("mqtt_password").value = myObj.mqtt_password;
    if (myObj.mqtt_sub) document.getElementById("mqtt_sub").value = myObj.mqtt_sub;

    // SPIFFS
    if (myObj.spiffs_t && myObj.spiffs_u) {
        GraphSPIFFS_t = Number(myObj.spiffs_t);
        GraphSPIFFS_u = Number(myObj.spiffs_u)
        GraphSPIFFS_f = GraphSPIFFS_t - GraphSPIFFS_u;
        document.getElementById("spiffs_t").value = GraphSPIFFS_t;
        document.getElementById("spiffs_u").value = GraphSPIFFS_u;
        document.getElementById("spiffs_f").value = GraphSPIFFS_f;

        diskspace_js.data.labels = ['Used ' + GraphSPIFFS_u, 'Free ' + GraphSPIFFS_f];
        diskspace_js.data.datasets[0].data = [GraphSPIFFS_u, GraphSPIFFS_f];
        diskspace_js.update();
    };


    if (myObj.time) {
        var date = new Date(myObj.time * 1000);
        document.getElementById("Time").innerHTML = ('0' + date.getDate()).slice(-2) + '/' + ('0' + (date.getMonth() + 1)).slice(-2) + '/' + date.getFullYear() + ' ' + ('0' + date.getHours()).slice(-2) + ':' + ('0' + date.getMinutes()).slice(-2);
    }

    if (Number(myObj.TemperatureG) && Number(myObj.HumidityG)) {
        GraphLabel.push('');
        GraphTemperatureG.push(Number(Number(myObj.TemperatureG).toFixed(1)));
        GraphHumidityG.push(Number(Number(myObj.HumidityG).toFixed(1)));
        upGraph();
    }
    if (Number(myObj.TemperatureD) && Number(myObj.HumidityD)) {
        GraphLabel.push('');
        GraphTemperatureD.push(Number(Number(myObj.TemperatureD).toFixed(1)));
        GraphHumidityD.push(Number(Number(myObj.HumidityD).toFixed(1)));
        upGraph();
    }
}

// Get all status
function get(cmd) {
    websocket.send(JSON.stringify({
        action: 'get' + cmd
    }));
}
function setParam() {
    websocket.send(JSON.stringify({
        action: 'setParam',
        tL: Number(document.getElementById("tL").value).toFixed(1),
        tH: Number(document.getElementById("tH").value).toFixed(1),
        hL: Number(document.getElementById("hL").value).toFixed(0),
        hH: Number(document.getElementById("hH").value).toFixed(0),
    }));
}
function setWifi() {
    websocket.send(JSON.stringify({
        action: 'setWifi',
        wifi_ssid: document.getElementById("wifi_ssid").value,
        wifi_key: document.getElementById("wifi_key").value,
        wifi_ap_mode: document.getElementById("wifi_ap_mode").value,
    }));
}
function setMqtt() {
    websocket.send(JSON.stringify({
        action: 'setMqtt',
        mqtt_host: document.getElementById("mqtt_host").value,
        mqtt_port: document.getElementById("mqtt_port").value,
        //mqtt_client_id: document.getElementById("mqtt_client_id").value,
        mqtt_username: document.getElementById("mqtt_username").value,
        mqtt_password: document.getElementById("mqtt_password").value,
        mqtt_sub: document.getElementById("mqtt_sub").value,
    }));
}
function setSpiffs() {
    websocket.send(JSON.stringify({
        action: 'setSpiffs',
    }));
}
function setRelay() {
    websocket.send(JSON.stringify({
        action: 'setRelay',
        r3: document.getElementById("r3s").checked,
        r4: document.getElementById("r4s").checked,
    }));
}

function deleteData() {
    if (confirm('are you sure ?')) {
        websocket.send(JSON.stringify({
            action: 'delete',
        }));
    }
}
function clearError() {
    websocket.send(JSON.stringify({
        action: 'clearError',
    }));
    alert("Error cleared.")
}

function openModal(modal) {
    get(modal);
    document.getElementById("modal-" + modal).classList.add("active");
}

function closeModal() {
    document.getElementById("modal-Param").classList.remove("active");
    document.getElementById("modal-Data").classList.remove("active");
    document.getElementById("modal-Mqtt").classList.remove("active");
    document.getElementById("modal-Wifi").classList.remove("active");
    document.getElementById("modal-Settings").classList.remove("active");
    document.getElementById("modal-Spiffs").classList.remove("active");
}

function csvToArrays(csv) {
    GraphLabel = [], GraphTemperatureG = [], GraphHumidityG = [];
    const content = csv.split('\n');
    content.forEach(line => {
        line = line.split(',');
        if (Number(line[0]) && Number(line[1]) && Number(line[2])) {
            GraphLabel.push('');
            GraphTemperatureG.push(Number(Number(line[1]).toFixed(1)));
            GraphHumidityG.push(Number(Number(line[2]).toFixed(1)));
        }
    });
    if (GraphLabel.length > 200) {
        let d = GraphLabel.length - 200;
        GraphLabel.splice(0, d);
        GraphTemperatureG.splice(0, d);
        GraphHumidityG.splice(0, d);
    }
    return { GraphLabel, GraphTemperatureG, GraphHumidityG };
}

function reloadGraph() {
    fetch('http://esp32.local/data.csv')
        .then(response => response.text())
        .then(vGraph => {
            csvToArrays(vGraph);
            upGraph();
        });
}

function upGraph() {
    if (GraphLabel.length == GraphTemperatureD.length && GraphLabel.length == GraphHumidityD.length) {
        chart_d.data.labels = GraphLabel;
        chart_d.data.datasets[0].data = GraphTemperatureD;
        chart_d.data.datasets[1].data = GraphHumidityD;
        chart_d.options = {
            scales: {
                y: {
                    beginAtZero: false
                }
            }
        }
        chart_d.update();
    }
    if (GraphLabel.length == GraphTemperatureG.length && GraphLabel.length == GraphHumidityG.length) {
        chart_g.data.labels = GraphLabel;
        chart_g.data.datasets[0].data = GraphTemperatureG;
        chart_g.data.datasets[1].data = GraphHumidityG;
        chart_g.options = {
            scales: {
                y: {
                    beginAtZero: false
                }
            }
        }
        chart_g.update();
    }
}
