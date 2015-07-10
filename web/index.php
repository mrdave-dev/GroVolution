<!DOCTYPE html>
<html>
<head>

<script>
function loadWebFetch() {
	var xmlhttp;
	if (window.XMLHttpRequest) {
		// code for modern browsers
		xmlhttp = new XMLHttpRequest();
	} else {
		// code for IE6, 5
		xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
	}

	xmlhttp.open("GET", "webfetch.php?t=" + Math.random(), true);
	xmlhttp.send();

	xmlhttp.onreadystatechange = function() {
		if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
			document.getElementById("content").innerHTML=xmlhttp.responseText;
		}
	}

}

function weballon() {
	var xmlhttp;
	if (window.XMLHttpRequest) {
		xmlhttp = new XMLHttpRequest();
	} else {
		xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
	}

	xmlhttp.open("GET", "weballon.php?t=" + Math.random(), true);
	xmlhttp.send();

	setTimeout(function() { loadWebFetch() }, 4000);
}

function weballoff() {
	var xmlhttp;
	if (window.XMLHttpRequest) {
		xmlhttp = new XMLHttpRequest();
	} else {
		xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
	}

	xmlhttp.open("GET", "weballoff.php?t=" + Math.random(), true);
	xmlhttp.send();

	setTimeout(function() { loadWebFetch() }, 4000);
}

function webtoggle() {
	var xmlhttp;
	if (window.XMLHttpRequest) {
		xmlhttp = new XMLHttpRequest();
	} else {
		xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
	}

	var rly = document.getElementById("relay").value;

	xmlhttp.open("GET", "webtoggle.php?r=" + rly + "&t=" + Math.random(), true);
	xmlhttp.send();

	setTimeout(function() { loadWebFetch() }, 4000);

}

</script>

</head>
<body>
<div id="content"><p>Click the button to load.</p></div>
<button type="button" onclick="loadWebFetch()">Load!</button>
<button type="button" onclick="weballon()">All On</button>
<button type="button" onclick="weballoff()">All Off</button>
<br />

<h2>Toggle Switch: <input type="text" id="relay"><button type="button" onclick="webtoggle()">ON/OFF</button></h2>


</body>
</html>
