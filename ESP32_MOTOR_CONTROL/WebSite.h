/*
 * 
 * This header file contains the HTML, CSS and JS
 * for the control website that is hosted on the
 * ESP32 WebServer
 * 
 * by Nathan Gray
 * G00379837
 * 10/04/21
 * 
 */ 
#ifndef WebSite_h
#define WebSite_h

String webpage = R"=====(
   <!DOCTYPE html>
  <html>
    <head>
      <style>
       body
        {
        background-color: #686e78
        }
        .main-container {
        display: flex;
        flex-direction: column;
        background-color: #686e78;
        margin-left: 10%;
        }
        .title-div {
        font: small-caps bold 24px/1 sans-serif;
        background-color: #686e78;
        width: 100%;
        height: 25px;
        text-align: center;
        border-radius: 10px;
        margin-bottom: 5px;
        }
        .content-div {
        display: flex;
        flex-direction: row;
        background-color: #686e78;
        width: 100%;
        height: 50%;
        }
        .camera-feed {
        background-color: #686e78;
        width: 600px;
        height: 500px;
        text-align: center;
        border: 1px solid black;
        border-radius: 60px;
        }
        .buttons-div {
        background-color: #686e78;
        width: 35%;
        height: 300px;
        text-align: center;
        margin-left: 4%;
        margin-right: 10%;
        margin-top: 5%;
        }
        .controls-div {
        background-color: #686e78;
        width: 100%;
        height: 100%;
        padding-top: 10px;
        padding-left: 25px;
        }
        .fire-div {
        display: flex;
        background-color: #686e78;
        width: 100%;
        height: 30%;
        justify-content: center;
        align-items: center;
        padding-left: 20px;
        padding-top: 120px;
        }
        .slider-div {
        background-color: #686e78;
        width: 3%;
        height: 500px;
        margin-left 300px;
        margin-top:4%
        
        }
        .button {
        background-color: #ff0000;
        width: 100px;
        height: 100px;
        border: 1px solid black;
        border-radius: 50%;
        transition-duration: 0.5s;
        cursor: pointer;
        box-shadow: 0 9px #c20000;
        margin-bottom: 170%;
        }
        .firebut{
        background-color: #7b828f;
        color: black; 
        border: 2px solid #ff0000;
        }
        .firebut:hover{
        background-color: #ff0000;
        color: white;
        }
        .firebut:active
        {
          background-color: #ff0000;
          box-shadow: 0 5px #940000;
          transform: translateY(4px);
          color: white;
        }
        .flex-row 
        {
        display: flex;
        flex-direction: row;
        background-color: #686e78;
        margin: 5px;
        }
        .movement
        {
        background-color: #800080; 
        color: white;
        padding: 10% 15%;
        text-align: center;
        text-decoration: none;
        display: inline-block;
        font-size: 16px;
        margin: 2% 1%;
        box-shadow: 0 9px #542954;
        transition-duration: 0.5s;
        cursor: pointer;
        }
        .mov 
        {
          background-color:#7b828f; 
          color: black; 
          border: 2px solid #800080;
        }
        .mov:hover 
        {
          background-color: #800080;
          color: white;
        }
        .mov:active
        {
          background-color: #800080;
          box-shadow: 0 5px #400040;
          transform: translateY(4px);
          color: white;
        }
        
        .slider 
        {
          -webkit-appearance: none;
          width: 50%;
          height: 97%;
          background: #d3d3d3;
          outline: none;
          opacity: 0.7;
          -webkit-transition: .2s;
          transition: opacity .2s;
          margin-top: 10%;
        }
  
        .slider:hover 
        {
          opacity: 1;
        }
        .slider::-webkit-slider-thumb 
        {
          -webkit-appearance: none;
          appearance: none;
          width: 25px;
          height: 25px;
          background: purple;
          
          cursor: pointer;
        }
  
      .slider::-moz-range-thumb 
      {
        width: 25px;
        height: 25px;
        background: purple;
        cursor: pointer;
      }
      </style>
      
      <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
      
    </head>
  
    <body>
      <div class="main-container">
        <div class="title-div">Tennis Ball Launcher</div>
        <div class="content-div">
          <img class="camera-feed" src = "http://192.168.15.222/stream">
          <div class="buttons-div">
            <div class="controls-div">
                <div class="flex-row" style = "justify-content: center; margin-top: 8%">
                  <button class="movement mov" onmousedown = "left(60);sendValues(x,pot,ammo);" onmouseup = "left(88);sendValues(x,pot,ammo);">LEFT</button>
                  <button class="movement mov" style = "margin-left: 10%" onmousedown = "right(100);sendValues(x,pot,ammo);" onmouseup = "right(88);sendValues(x,pot,ammo);" >RIGHT</button>
                </div>
              </div>
            <div class="fire-div">
                <div><button class="button firebut" onmousedown ="setAmmo(1);sendValues(x,pot,ammo);" onmouseup ="setAmmo(0);sendValues(x,pot,ammo);">FIRE</button></div>
              </div>
          </div>
          <div class="slider-div">
            <input type= "range" min= "0" max= "255" value= "50" class= "slider" id= "pwmSlider" orient = vertical onchange = "pwm(this.value); sendValues(x,pot,ammo);"/>
          </div>
        </div>
      </div>
      
      <script>
        $.ajaxSetup({timeout:1000});
        
        var x_axis;
        var x = 88;
        var pot = 100;
        var ammo = 0;
        
        function pwm(slider)
        {
          pot = slider;
        }
        function left(l)
        {
          x = l;
        }
        function right(r)
        {
          x = r;
        }
        function setAmmo(a)
        {
          ammo = a;
        }
        
        function sendValues(x,pot,ammo)
        {
          $.get("/?value=" + x + "," + pot + "," + ammo + "," + "&");
        }

      </script>
     
    </body>
  </html>
  )=====";
#endif
