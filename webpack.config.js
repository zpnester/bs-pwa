const path = require("path");

const HtmlWebpackPlugin = require("html-webpack-plugin")
const CopyWebpackPlugin = require("copy-webpack-plugin")

module.exports = {
    mode: process.env.NODE_ENV || "development",
    entry: {
        sw: "./test/Sw.bs.js",
        main: "./test/Main.bs.js"
    },
    output: {
        path: path.resolve(__dirname, "test_dist"),
        filename: "[name].js"
    },
    plugins: [
        new HtmlWebpackPlugin({
            template: "./test/index.html",
            inject: true,
            chunks: ["main"]
        }),
        new CopyWebpackPlugin([
            { from: 'static', to: "" },
        ])
    ]
};