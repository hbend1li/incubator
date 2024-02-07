var gateway = `ws://${window.location.hostname}/ws`;
var websocket;
var GraphTemperature = [], GraphLabelT = [], GraphHumidity = [], GraphLabelH = [];
var GraphSPIFFS_t = 0, GraphSPIFFS_u = 0, GraphSPIFFS_f = 0;
window.addEventListener('load', onLoad);

var chartT = new Chart(document.getElementById('myChartCanvasT'), {
    type: 'line',
    data: {
        labels: [],
        datasets: [{
            label: 'Temperature',
            data: [],
            borderWidth: 2,
            cubicInterpolationMode: 'monotone',
            borderColor: '#ffb700',
            backgroundColor: '#ffb700',
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

var chartH = new Chart(document.getElementById('myChartCanvasH'), {
    type: 'line',
    data: {
        labels: [],
        datasets: [{
            label: 'Humidity',
            data: [],
            borderWidth: 2,
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
    //console.log(myObj);

    if (Number(myObj.Temperature)) {
        document.getElementById("Temperature").innerHTML = Number(myObj.Temperature).toFixed(1)
        GraphTemperature.push(Number(Number(myObj.Temperature)));
        GraphLabelT.push('');
        let l = GraphLabelT.length - 200;
        if (GraphLabelT.length > 0) {
            GraphLabelT.splice(0, l);
            GraphTemperature.splice(0, l);
        }
        upGraphT();
    }

    if (Number(myObj.Humidity)) {
        document.getElementById("Humidity").innerHTML = Number(myObj.Humidity).toFixed(0);
        GraphHumidity.push(Number(Number(myObj.Humidity)));
        GraphLabelH.push('');
        let l = GraphLabelH.length - 200;
        if (GraphLabelH.length > 0) {
            GraphLabelH.splice(0, l);
            GraphHumidity.splice(0, l);
        }
        upGraphH();
    }

    // Thermosta
    if (myObj.tL) document.getElementById("tL").value = Number(myObj.tL).toFixed(1);
    if (myObj.tH) document.getElementById("tH").value = Number(myObj.tH).toFixed(1);
    if (myObj.hL) document.getElementById("hL").value = Number(myObj.hL).toFixed(0);
    if (myObj.hH) document.getElementById("hH").value = Number(myObj.hH).toFixed(0);
    // Relay 1-4

    if (myObj.r1 === true || myObj.r1 === false) {
        document.getElementById("r1s").checked = myObj.r1;
        //document.getElementById("r1span").innerHTML = myObj.r1 ? 'ON' : 'OFF';
    }
    if (myObj.r2 === true || myObj.r2 === false) {
        document.getElementById("r2s").checked = myObj.r2;
        //document.getElementById("r2span").innerHTML = myObj.r2 ? 'ON' : 'OFF';
    }
    if (myObj.r3 === true || myObj.r3 === false) {
        document.getElementById("r3s").checked = myObj.r3;
        //document.getElementById("r3span").innerHTML = myObj.r3 ? 'ON' : 'OFF';
    }
    if (myObj.r4 === true || myObj.r4 === false) {
        document.getElementById("r4s").checked = myObj.r4;
        //document.getElementById("r4span").innerHTML = myObj.r4 ? 'ON' : 'OFF';
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
        //document.getElementById("Time").innerHTML = ('0' + date.getDate()).slice(-2) + '/' + ('0' + (date.getMonth() + 1)).slice(-2) + '/' + date.getFullYear() + ' ' + ('0' + date.getHours()).slice(-2) + ':' + ('0' + date.getMinutes()).slice(-2);
        document.getElementById("Time").innerHTML = ('0' + date.getHours()).slice(-2) + ':' + ('0' + date.getMinutes()).slice(-2) + ':' + ('0' + date.getSeconds()).slice(-2);
    }


}

// Get all status
function get(cmd) {
    websocket.send(JSON.stringify({
        cmd: 'get' + cmd
    }));
}
function setParam() {
    websocket.send(JSON.stringify({
        cmd: 'setParam',
        tL: Number(document.getElementById("tL").value).toFixed(1),
        tH: Number(document.getElementById("tH").value).toFixed(1),
        hL: Number(document.getElementById("hL").value).toFixed(0),
        hH: Number(document.getElementById("hH").value).toFixed(0),
    }));
}
function setWifi() {
    websocket.send(JSON.stringify({
        cmd: 'setWifi',
        wifi_ssid: document.getElementById("wifi_ssid").value,
        wifi_key: document.getElementById("wifi_key").value,
        wifi_ap_mode: document.getElementById("wifi_ap_mode").value,
    }));
}
function setMqtt() {
    websocket.send(JSON.stringify({
        cmd: 'setMqtt',
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
        cmd: 'setSpiffs',
    }));
}
function setRelay() {
    websocket.send(JSON.stringify({
        cmd: 'setRelay',
        r3: document.getElementById("r3s").checked,
        r4: document.getElementById("r4s").checked,
    }));
}

function deleteData() {
    if (confirm('are you sure ?')) {
        websocket.send(JSON.stringify({
            cmd: 'delete',
        }));
    }
}
function clearError() {
    websocket.send(JSON.stringify({
        cmd: 'clearError',
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
    GraphLabelT = [], GraphTemperature = [], GraphLabelH = [], GraphHumidity = [];
    const content = csv.split('\n');
    content.forEach(line => {
        line = line.split(',');
        if (Number(line[0]) && Number(line[1]) && Number(line[2])) {
            GraphLabelT.push('');
            GraphLabelH.push('');
            GraphTemperature.push(Number(Number(line[1])));
            GraphHumidity.push(Number(Number(line[2])));
        }
    });
    if (GraphLabelT.length > 200) {
        let d = GraphLabelT.length - 200;
        GraphLabelT.splice(0, d);
        GraphLabelH.splice(0, d);
        GraphTemperature.splice(0, d);
        GraphHumidity.splice(0, d);
    }
    return { GraphLabelT, GraphTemperature, GraphLabelH, GraphHumidity };
}

function reloadGraph() {
    fetch('http://esp32.local/data.csv')
        .then(response => response.text())
        .then(vGraph => {
            //csvToArrays(vGraph);
            upGraphT();
            upGraphH();
        });
}

function upGraphT() {
    chartT.data.labels = GraphLabelT;
    chartT.data.datasets[0].data = GraphTemperature;
    chartT.options = {
        scales: {
            y: {
                beginAtZero: false
            }
        }
    }
    chartT.update();
}
function upGraphH() {
    chartH.data.labels = GraphLabelH;
    chartH.data.datasets[0].data = GraphHumidity;
    chartH.options = {
        scales: {
            y: {
                beginAtZero: false
            }
        }
    }
    chartH.update();
}
