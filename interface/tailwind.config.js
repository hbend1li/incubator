module.exports = {
  darkMode: 'class',
  content: ['./public/*.html'],
  plugins: [
    require("@tailwindcss/typography"),
    require('daisyui')
  ],
  daisyui: {
    themes: ["light", "dark"],
  },
};
