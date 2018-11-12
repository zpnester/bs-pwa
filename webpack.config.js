const path = require("path");

module.exports = {
    mode: process.env.NODE_ENV || "development",
    entry: "./test/Sw.bs.js",
    output: {
        path: path.resolve(__dirname, "test_dist"),
        filename: "sw.wp.js"
    }
};