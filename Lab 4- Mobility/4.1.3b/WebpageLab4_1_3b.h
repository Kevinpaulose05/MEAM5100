const char body[] PROGMEM = R"===(
<!DOCTYPE html>  
<html>
<body>        
  <h1>LED Control</h1>
  <p>Duty Cycle Control:
    <input type="range" min="0" max="100" value="50" id="brightnessSlider" oninput="updateBrightness(this.value)">
    <span id="brightness">128</span>
  </p>
  <p>Frequency Control:
    <input type="range" min="3" max="30" value="15" id="frequencySlider" oninput="updateFrequency(this.value)">
    <span id="frequency">15</span>
  </p>
  <script>
    function updateBrightness(val) {
      document.getElementById('brightness').innerText = val;
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/brightness?value=" + val, true);
      xhr.send();
    }

    function updateFrequency(val) {
      document.getElementById('frequency').innerText = val;
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/frequency?value=" + val, true);
      xhr.send();
    }
  </script>
</body>
</html>
)===";