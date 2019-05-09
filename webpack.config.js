const path = require("path");

const CopyWebpackPlugin = require("copy-webpack-plugin")

module.exports = {
    mode: process.env.NODE_ENV || "development",
    entry: {
        sw: "./test/Sw.bs.js",
        main: "./test/Main.bs.js",
        rtc: "./test/Rtc.bs.js",
        "rtc-peer-band": "./test/RtcPeerBand.bs.js",
        "rtc-dc-basic": "./test/RtcDcBasic.bs.js",
        "worker-example": "./test/WorkerExample.bs.js",
        "worker-readme-example": "./test/WorkerReadmeExample.bs.js",
        "worker-src": "./test/WorkerSrc.bs.js",
        "doWork": "./test/WorkerReadmeSrc.bs.js",
        "react-example": "./test/ReactExample.bs.js",
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