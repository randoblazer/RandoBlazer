<?php
include('up.php');

// définition de variable
if(!empty($_GET['id'])){
	$profileID	=	$_GET['id'];
	if(empty($_SESSION['id'])){
		$sessionID = 0;
	}else{
		$sessionID = $_SESSION['id'];
	}
	if($sessionID==0 || $sessionID!=$profileID){
// la jolie bouboucle
		$sql        =   'SELECT username,location,gender,birthday,twitch,comment FROM user WHERE id='.$profileID.' ORDER BY username ASC';
		$stmt       =   $db->prepare($sql);
		?>
		<h2>Profile</h2>
		<table class='table' border='0'>
			<?php
			if($stmt->execute()){
				while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
					?>
					<tr>
						<td>Username : </td>
						<td><?php echo $row['username'];?></td>
					</tr>
					<?php
					if(!empty($row['location'])){
						?>
						<tr>
							<td>Location : </td>
							<td><?php echo $row['location'];?></td>
						</tr>
						<tr>
							<td>Gender : </td>
							<?php if($row['gender']==1){echo "<td>Female</td>";}?>
							<?php if($row['gender']==2){echo "<td>Male</td>";}?>
							<?php if($row['gender']==3){echo "<td>Other</td>";}?>
							<?php if($row['gender']==4){echo "<td>Not specified</td>";}?>
						</tr>
						<?php
					}
					?>
					<tr>
						<?php
						if($row['birthday']!="0000-00-00 00:00:00"){
							?>
							<td>Birthday : </td>
							<td><?php 

						// définition et formatage de la date d'anniversaire
							$birthdayPure 	= 	new dateTime($row['birthday']);
							$birthday 		=	$birthdayPure->format('Y-m-d');
							$birthdayOutput = $beginingDateFormated = strftime("%e %B %Y",strtotime($birthday));
						// calcul de l'âge
							$today = new dateTime();
							$diff = $today->diff($birthdayPure);
							$age = $diff->format('%Y');
						// affichage
							echo $birthdayOutput." (".$age." years old)";
							?></td>
						</tr>
						<?php
					}
					?>
					<tr>
						<td>Twitch channel : </td>
						<td><?php echo "<a href='https://www.twitch.tv/".$row['twitch']."' target='_blank'>".$row['twitch']."</a>";?></td>
					</tr>
					<tr>
						<td>Biography : </td>
						<td><?php echo $row['comment'];?></td>
					</tr>
					<tr>
						<td>Average time : </td>
						<td><?php
					// calcul de la moyenne de temps
						$sql        =   'SELECT timeSent FROM times WHERE fk_user_id='.$profileID.'';
						$j 			=	0;
						$stmt       =   $db->prepare($sql);
						$somme		=	0;
						$i 			=	0;
						if($stmt->execute()){
							while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
								$j++;
							$dateTime = new dateTime($row['timeSent']); //H:i:s
							$hours = $dateTime->format('H'); 
							$minutes = $dateTime->format('i');
							$seconds = $dateTime->format('s');

							// calculs
							$somme += $hours*3600;
							$somme += $minutes*60;
							$somme += $seconds;
							$i++;
						}
					}
					if($j>0){
						// calcul final
						$totalSeconds 	= $somme/$i;
						$days 			= floor($totalSeconds/86400);
						$day_sec 		= $days*86400;
						$hours 			= floor( ($totalSeconds-$day_sec) / (60 * 60) );
						$hour_sec 		= $hours*3600;
						$minutes		= floor((($totalSeconds-$day_sec)-$hour_sec)/60);
						$min_sec 		= $minutes*60;
						$seconds 		= floor(($totalSeconds-$day_sec)-$hour_sec)-$min_sec;

						// formatage éléments
						$hours 			= str_pad($hours,2,"0",STR_PAD_LEFT);
						$minutes 		= str_pad($minutes,2,"0",STR_PAD_LEFT);
						$seconds 		= str_pad($seconds,2,"0",STR_PAD_LEFT);

						$result 		= '0000-00-00 '.$hours.':'.$minutes.':'.$seconds;
						$result			= new dateTime($result);
						$resultOutput	= $result->format('H:i:s');
					}
					

					// affichage
					if($j>0){
						echo $resultOutput;
					}else{
						echo "No time posted for now. ";
					}
					
					?></td>
				</tr>

				<?php
			}
		}
		?>
	</table>
	
	<?php
}
// si c'est son profile

// traitement en cas d'envoi
if(isset($_POST['username']) && isset($_POST['twitch']) && isset($_POST['location']) && isset($_POST['birthday']) && isset($_POST['gender']) ){
    // variable names recovery
	$username       =   "'".$_POST['username']."'";
	$twitch         =   "'".$_POST['twitch']."'";
	$location      	=   "'".addslashes($_POST['location'])."'";
	$birthday     	=   "'".$_POST['birthday']."'";
	$gender 	    =   "'".$_POST['gender']."'";
	$comment 		=	"'".addslashes($_POST['comment'])."'";
	$result         =   0;
	$errors         =   0;

	$sql        =   'SELECT username FROM user WHERE id='.$profileID;
	$stmt       =   $db->prepare($sql);
	if($stmt->execute()){
		while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
			$oldUsername;
		}
	}

    // controlling datas
    // username
	if (!preg_match("/^[a-zA-Z0-9\-\_' éàèôûùî]*$/",$username)) {
		$usernameErr = "Format is not valid";
		$errors++;
	}
        // contrôle si le pseudo est déjà pris
	$i 		=	0;
	$sql    =   'SELECT id FROM user WHERE username='.$username;
	$stmt   =   $db->prepare($sql);
	if($stmt->execute()){
		while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
			$i++;
		}
	}
	if(!empty($oldUsername)){
		if($username!=$oldUsername){
			if ($i>0){
				$usernameErr2 = "This username is already used.";
				$errors++;
			}
		}
	}

    // twitch
	if (!preg_match("/^[a-zA-Z0-9\-\_' éàèôûùî]*$/",$twitch)) {
		$twitchErr = "Format is not valid";
		$errors++;
	}

    // sortie de la boucle en cas d'erreur de format
	if($errors===0){        
		$result = 1;
		if($result===1){
            // worker line cration on workers tab
			$sql        =   "UPDATE user 
			SET username=".$username.", twitch=".$twitch.", location=".$location.", 
			birthday=".$birthday.", gender=".$gender.", comment=".$comment." 
			WHERE id=".$_SESSION['id'];
			$stmt       =   $db->prepare($sql);
			if($stmt->execute()){
				while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
					$result++;
				}
			}
			unset($_POST);
            // message de réussite ou redirection
			$link 	=	"profile.php?id=".$_SESSION['id'];
            // header('location: '.$link);
		}else{
			echo '<p>Une erreur est survenue, prière de modifier les champs nécessaires</p>'; 
		}
	}
}

// récupération de ses données
$sql        =   'SELECT username,location,gender,birthday,twitch,comment FROM user WHERE id='.$profileID.' ORDER BY username ASC';
$stmt       =   $db->prepare($sql);
if($stmt->execute()){
	while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
		$username 	=	$row['username'];
		$location 	=	$row['location'];
		$gender 	=	$row['gender'];
		$birthday 	= 	new dateTime($row['birthday']);
		$birthday 		=	$birthday->format('Y-m-d');
		$twitch 	=	$row['twitch'];
		$comment 	=	$row['comment'];
	}
}
// formulaire
if($sessionID>0 && $sessionID==$profileID){
	?>
	<form method="post">
		<div class="form-row">
			<div class="form-group col-md-6">
				<label>Username</label>
				<input type="text" name="username" class="form-control" <?php if(!empty($username)){echo 'value="'.$username.'"';}?> required />
				<?php
				if(isset($usernameErr)){
					echo '&nbsp;<font color="red">'.$usernameErr.'</font>';
				}
				if(isset($usernameErr2)){
					echo '&nbsp;<font color="red">'.$usernameErr2.'</font>';
				}
				?>
			</div>
			<div class="form-group col-md-6">
				<label>Twitch username</label>
				<input type="text" name="twitch" class="form-control" <?php if(!empty($twitch)){echo 'value="'.$twitch.'"';}?> required />
				<?php
				if(isset($twitchErr)){
					echo '&nbsp;<font color="red">'.$twitchErr.'</font>';
				}
				?>
			</div>
		</div>
		<div class="form-row">
			<div class="form-group col-md-6">
				<label>Location</label>
				<input type="text" name="location" class="form-control" placeholder="City, country/state"<?php if(!empty($location)){echo 'value="'.$location.'"';}?> />
				<?php
				if(isset($locationErr)){
					echo '&nbsp;<font color="red">'.$locationErr.'</font>';
				}
				?>
			</div>
			<div class="form-group col-md-6">
				<label>Birthday</label>
				<input type="date" name="birthday" class="form-control" <?php if(!empty($birthday)){echo 'value="'.$birthday.'"';}?> />
				<?php
				if(isset($birthdayErr)){
					echo '&nbsp;<font color="red">'.$birthdayErr.'</font>';
				}
				?>
			</div>
		</div>

		<div class="form-row">
			<div class="form-group col-md-6">
				<label>Gender</label>
				<select name="gender" class="form-control chosen">
					<option>Select one</option>
					<option value="1" <?php if($gender==1)echo"selected";?>>Female</option>
					<option value="2" <?php if($gender==2)echo"selected";?>>Male</option>
					<option value="3" <?php if($gender==3)echo"selected";?>>Other</option>
					<option value="4" <?php if($gender==4)echo"selected";?>>Not specified</option>
				</select>
			</div>
		</div>

		<div class="form-row">
			<div class="form-group col-md-12">
				<label>Biography</label>
				<textarea class="form-control" name="comment" id="comment" rows="3"><?php if(!empty($comment)){echo $comment;}?></textarea>
				<?php
				if(isset($commentErr)){
					echo '&nbsp;<font color="red">'.$commentErr.'</font>';
				}
				?>
			</div>
		</div>

		<div class="form-row">
			<div class="form-group col-md">
				<button type="submit" class="btn btn-primary">Update</button>
			</div>
		</div>
	</form>

	<?php
}
	// gestion du temps
$dateTime = new dateTime('', new DateTimeZone('Europe/Berlin'));
	// numéro de semaine
$weekNumber = $dateTime->format('W');
	// annéee
$year = $dateTime->format('Y');

	// test si seed postée
$sql        =   'SELECT year, week, timeSent FROM times WHERE fk_user_id='.$profileID.' ORDER BY year ASC, week ASC';
$stmt       =   $db->prepare($sql);
$i 			=	0;
if($stmt->execute()){
	while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
		if($row['year']==$year && $row['week']>=$weekNumber){
		}else{
			$i++;
		}
	}
}
if($i>0){
	?>
	<h2>Seeds</h2>
	<table class='table' border='0'>
		<tr>
			<thead>
				<th scope='col'>Year</th>
				<th scope='col'>Week</th>
				<th scope='col'>Time</th>
				<th scope='col'>Rank</th>
			</thead>
		</tr>
		<?php
	// boucle de ses grands morts
		$sql        =   'SELECT year, week, timeSent FROM times WHERE fk_user_id='.$profileID.' ORDER BY year ASC, week ASC';
		$stmt       =   $db->prepare($sql);
		if($stmt->execute()){
			while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
				if($row['year']==$year && $row['week']>=$weekNumber){
				// ne pas afficher la seed de la semaine en cours
				}else{
				// on affiche les lignes
					$timeList		= 	new dateTime($row['timeSent']);
					$timeListOutput	= 	$timeList->format('H:i:s');
					$rank 			=	weeklySeedUserRanking($profileID, $row['year'], $row['week'], $db);
					echo "<tr><td>".$row['year']."</td><td>".$row['week']."</td><td>".$timeListOutput."</td><td>".$rank."</td></tr>";
				}
			}
		}
		echo "</table>";
		}
		if($i>1){
		?>
		<h2>Graphs</h2>
		<?php

	// boucle pour mettre les valeurs dans un array
	$array1 = 	array(); // array de rangs
	$array2	=	array(); // array de temps
	$sql        =   'SELECT year,week,timeSent FROM times WHERE fk_user_id='.$profileID.' ORDER BY year ASC, week ASC';
	$stmt       =   $db->prepare($sql);
	if($stmt->execute()){
		while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
			$timeSentListBrut	=	new dateTime($row['timeSent']);
			$timeSentListOutput	= 	$timeSentListBrut->format('H.is');
			$timeSentListOutput	=	$timeSentListOutput*10000;

			$x1	=	substr($row['year'], 2, 2)."-".$row['week'];
			$y1 =	weeklySeedUserRanking($profileID, $row['year'], $row['week'], $db);
			$x2	=	$x1;
			$y2	=	$timeSentListOutput;

			// ajout au premier array (rangs)
			$arrayTMP	=	array("label"=>$x1, "y"=>$y1);
			array_push($array1, $arrayTMP);

			// ajout au second array (temps) // {x: new Date( Date.UTC (2012, 01, 1,2,0) ), y: 38  }
			$arrayTMP	=	array("label"=>$x2, "y"=>$y2);
			array_push($array2, $arrayTMP);
		}
	}
	?>
	<div id="chartContainer1" style="height: 370px; width: 100%;"></div>
	<br>
	<div id="chartContainer2" style="height: 370px; width: 100%;"></div>
	<br><br><br><br>
	<?php
}
}
include('down.php');
?>