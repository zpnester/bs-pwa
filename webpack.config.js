const path = require("path");

module.exports = {
    mode: process.env.NODE_ENV || "development",
    entry: {
        sw: "./test/Sw.bs.js",
        main: "./test/Main.bs.js"
    },
    output: {
        path: path.resolve(__dirname, "test_dist"),
        filename: "[name].wp.js"
    }
};