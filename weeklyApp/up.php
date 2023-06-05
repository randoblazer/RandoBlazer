<?php
include 'config.php';
?>
<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>Randoblazer Weekly</title>
	<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootswatch/4.5.2/superhero/bootstrap.min.css">
	<link rel="shortcut icon" href="favicon.ico" type="image/x-icon">
	<link rel="icon" href="favicon.ico" type="image/x-icon">
	<script type="stylesheet" href="index.css"></script>
</head>
<body>
	<nav class="navbar navbar-expand-lg navbar-dark bg-dark">
		<a class="navbar-brand" href="index.php">Randoblazer</a>
		<button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarColor02" aria-controls="navbarColor02" aria-expanded="false" aria-label="Toggle navigation">
			<span class="navbar-toggler-icon"></span>
		</button>

		<div class="collapse navbar-collapse" id="navbarColor02">
			<ul class="navbar-nav mr-auto">
				<li class="nav-item">
					<!-- <li class="nav-item active"> -->
					<a class="nav-link" href="weeklySeed.php">Current weekly seed</a>
				</li>
				<li class="nav-item">
					<a class="nav-link" href="rules.php">Rules</a>
				</li>
				<li class="nav-item">
					<a class="nav-link" href="runners.php">Runners</a>
				</li>
				<?php
				if(empty($_SESSION['id'])){
				?>
				<li class="nav-item">
					<a class="nav-link" href="login.php">Login</a>
				</li>
				<li class="nav-item">
					<a class="nav-link" href="register.php">Register</a>
				</li>
				<?php
				}else{
                    if(isset($_SESSION['is_admin'])){
                        if($_SESSION['is_admin']==1){
                            ?>
                <li class="nav-item">
                    <a class="nav-link" href="manageAdmins.php">Managing admins</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="manageTimes.php">Managing times</a>
                </li>
                            <?php
                        }
                    }
				?>
				<li class="nav-item">
					<a class="nav-link" href="index.php?nav=logout">Logout</a>
				</li>
				<li class="nav-item">
					<a class="nav-link" href="profile.php?id=<?php echo $_SESSION['id'];?>">My profile</a>
				</li>
				<?php
				}
				?>
				<li class="nav-item">
					<a class="nav-link" href="resources.php">Resources</a>
				</li>
			</ul>
		</div>
	</nav>
	<br>
	<div class="container">