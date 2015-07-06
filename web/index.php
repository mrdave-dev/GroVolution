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
</script>

</head>
<body>
<div id="content"><p>Click the button to load.</p></div>
<button type="button" onclick="loadWebFetch()">Load!</button>

</body>
</html>
