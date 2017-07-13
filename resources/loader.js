function toggleOutput() {
    var outputStyle = document.getElementById('output').style;
    var showButton = document.getElementById('show');
    if (outputStyle.display == "block") {
        outputStyle.display = "none";
        showButton.value = "Show console";
    } else {
        outputStyle.display = "block";
        showButton.value = "Hide console";
    }
};

var statusElement = document.getElementById('status');
var progressElement = document.getElementById('progress');
var spinnerElement = document.getElementById('spinner');

var Module = {
    preRun: [],
    postRun: [],
    print: (function() {
        var element = document.getElementById('output');
        if (element) {
            // clear browser cache
            element.value = '';
        }
        return function(text) {
            if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');
            console.log(text);
            if (element) {
                element.value += text + "\n";
                // focus on bottom
                element.scrollTop = element.scrollHeight;
            }
        };
    })(),
    printErr: function(text) {
        if (arguments.length > 1) {
            text = Array.prototype.slice.call(arguments).join(' ');
        }
        console.error(text);
    },
    canvas: (function() {
        var canvas = document.getElementById('canvas');
        canvas.addEventListener("webglcontextlost", function(e) {
            alert('WebGL context lost. You will need to reload the page.');
            e.preventDefault();
        }, false);

        return canvas;
    })(),
    setStatus: function(text) {
        if (!Module.setStatus.last) Module.setStatus.last = { time: Date.now(), text: '' };
        if (text === Module.setStatus.text) return;
        var m = text.match(/([^(]+)\((\d+(\.\d+)?)\/(\d+)\)/);
        var now = Date.now();
        if (m && now - Date.now() < 30) return; // if this is a progress update, skip it if too soon
        if (m) {
            text = m[1];
            progressElement.value = parseInt(m[2])*100;
            progressElement.max = parseInt(m[4])*100;
            progressElement.hidden = false;
            spinnerElement.hidden = false;
        } else {
            progressElement.value = null;
            progressElement.max = null;
            progressElement.hidden = true;
            if (!text) spinnerElement.style.display = 'none';
        }
        statusElement.innerHTML = text;
    },
    totalDependencies: 0,
    monitorRunDependencies: function(left) {
        this.totalDependencies = Math.max(this.totalDependencies, left);
        Module.setStatus(left ? 'Preparing... (' + (this.totalDependencies-left) + '/' + this.totalDependencies + ')' : 'All downloads complete.');
    }
};

Module.setStatus('Downloading...');

window.onerror = function(event) {
    Module.setStatus('Exception thrown, see JavaScript console');
    spinnerElement.style.display = 'none';
    Module.setStatus = function(text) {
        if (text) Module.printErr('[post-exception status] ' + text);
    };
};

var emterpretXHR = new XMLHttpRequest();
emterpretXHR.open('GET', 'breakout.bin', true);
emterpretXHR.responseType = 'arraybuffer';
emterpretXHR.onload = function() {
    Module.emterpreterFile = emterpretXHR.response;

    var script = document.createElement('script');
    script.src = "breakout.js";
    document.body.appendChild(script);
};

emterpretXHR.send(null);
