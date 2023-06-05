<?php
include('up.php');
?>
<div class="jumbotron">
	<h1 class="display-3">Welcome!</h1>
	<p class="lead">This is a web app for randoblazer's community made by Neta.</p>
	<?php
	if(isset($_SESSION['id'])){
		echo '<p>You\'re correctly logged in!</p>';
		}else{
			echo '<p>Please log in on the login page!</p>';
		}
		?>
		</div>

		<?php
		include('down.php');
		?>