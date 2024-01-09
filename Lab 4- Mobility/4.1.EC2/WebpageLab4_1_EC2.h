const char body[] PROGMEM = R"===(
<!DOCTYPE html>
<html>
  <body>
    <h1 style="color:red">Kevin Paulose motor control lab 4.1.4</h1>
    <p>Motor Speed</p>
    <input type="range" min="0" max="100" value="50" id="motorSpeed">
    <span id="speedValue">50%</span> Speed <br>
    <p>Direction </p>
    <button style="color:green" id="forwardButton" onclick="MotorState('forward')">FORWARD</button>
    <button style="color:red" id="stopButton" onclick="MotorState('STOP')">STOP</button>
    <button style="color:blue" id="backwardButton" onclick="MotorState('reverse')">REVERSE</button>

    <script>
      var motorSpeed = document.getElementById("motorSpeed");
      var speedValue = document.getElementById("speedValue");

      motorSpeed.oninput = function() {
        var xhr1 = new XMLHttpRequest();
        xhr1.onreadystatechange = function() {
          if (xhr1.readyState === 4 && xhr1.status === 200) {
            speedValue.innerHTML = xhr1.responseText;
          }
        };
        xhr1.open("GET", "/motor?speed=" + motorSpeed.value, true);
        xhr1.send();
      };

      function MotorState(state) {
        var xhr2 = new XMLHttpRequest();
        xhr2.onreadystatechange = function() {
          if (xhr2.readyState === 4 && xhr2.status === 200) {
            // Optional: handle the response if needed
          }
        };
        xhr2.open("GET", "/motor?direction=" + state, true);
        xhr2.send();
      };
    </script>
  </body>
</html>
)===";