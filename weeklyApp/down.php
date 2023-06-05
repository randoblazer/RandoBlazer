</div>
	<script src="https://code.jquery.com/jquery-3.5.1.min.js" integrity="sha256-9/aliU8dGd2tb6OSsuzixeV4y/faTqgFtohetphbbj0=" crossorigin="anonymous"></script>
	<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js"></script>
	<script>
	window.onload = function () {
     
    var chart = new CanvasJS.Chart("chartContainer1", {
    	animationEnabled: false,
    	//theme: "light2",
    	title:{
    		text: "Ranking evolution"
    	},
    	axisX:{
    		crosshair: {
    			enabled: false,
    			snapToDataPoint: true
    		}
    	},
    	axisY:{
    		title: "Ranks",
    		includeZero: true,
    		minimum: 1,
    		reversed: true,
    		crosshair: {
    			enabled: false,
    			snapToDataPoint: true
    		}
    	},
    	toolTip:{
    		enabled: false
    	},
    	data: [{
    		type: "area",
    		fillOpacity: 0,
    		dataPoints: <?php echo json_encode($array1, JSON_NUMERIC_CHECK); ?>
    	}]
    });
    chart.render();

    var chart = new CanvasJS.Chart("chartContainer2", {
    	animationEnabled: false,
    	//theme: "light2",
    	title:{
    		text: "Timing evolution"
    	},
    	axisX:{
    		crosshair: {
    			enabled: false,
    			snapToDataPoint: true
    		}
    	},
    	axisY:{
    		valueFormatString: "##:##:##",
    		title: "Times",
    		includeZero: true,
    		crosshair: {
    			enabled: false,
    			snapToDataPoint: true
    		}
    	},
    	toolTip:{
    		enabled: false
    	},
    	data: [{
    		type: "area",
    		fillOpacity: 0,
    		dataPoints: <?php echo json_encode($array2, JSON_NUMERIC_CHECK); ?>
    	}]
    });
    chart.render();
     
    }
	</script>
    <script src="https://canvasjs.com/assets/script/canvasjs.min.js"></script>
    <script src="https://www.google.com/recaptcha/api.js"></script>
    <script>
        function onSubmit(token) {
            document.getElementById("registerForm").submit();
        }
    </script>
</body>
</html>	