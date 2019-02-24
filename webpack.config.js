const path = require("path");

const CopyWebpackPlugin = require("copy-webpack-plugin")

module.exports = {
    mode: process.env.NODE_ENV || "development",
    entry: {
        sw: "./test/Sw.bs.js",
        main: "./test/Main.bs.js",
        rtc: "./test/Rtc.bs.js"
    },
    output: {
        path: path.resolve(__dirname, "test_dist"),
        filename: "[name].js"
    },
    plugins: [
        new CopyWebpackPlugin([
            { from: 'static', to: "" },
        ])
    ]
};