<?php
include('up.php');

// la jolie bouboucle
$sql        =   'SELECT id,username,location FROM user ORDER BY username ASC';
$stmt       =   $db->prepare($sql);
echo "<h2>Runners</h2>";
echo "<table class='table' border='0'>";
echo "<tr><thead><th scope='col'>Username</th><th scope='col'>Location</th></thead></tr>";
if($stmt->execute()){
	while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
		$profileURL = 'profile.php?id='.$row['id'];
		echo "<tr><td><a href='".$profileURL."'>".$row['username']."</a></td><td><a href='".$profileURL."'>".$row['location']."</a></td></tr>";	
	}
}
echo "</table>";
?>


<?php
include('down.php');
?>