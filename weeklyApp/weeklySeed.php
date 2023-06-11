<?php
include('up.php');
// définition variable
if(!empty($_SESSION['id'])){
    $userID = $_SESSION['id'];
}
if(!empty($_GET['weekNumber'])){
    $getWeekNumber = $_GET['weekNumber'];
}else{
    $getWeekNumber = -1;
}
if(!empty($_GET['year'])){
    $getYear = $_GET['year'];
}else{
    $getYear = -1;
}

// Traitement du temps
$dateTime = new dateTime('', new DateTimeZone('Europe/Berlin'));
// numéro de jour de semaine (vendredi 5, samedi 6, dimanche 7, lundi 1, etc...)
$dayNumber = $dateTime->format('N');
// heure de la journée
$hourNumber = $dateTime->format('H');
// numéro de semaine
if(!isset($_GET['weekNumber'])){
    $weekNumber = $dateTime->format('W');
    if($dayNumber == 1 || $dayNumber == 2 || $dayNumber == 3 || $dayNumber == 4 || $dayNumber == 5){
        $weekNumber = intval($weekNumber)-1;
    }

}else{
    $weekNumber = $_GET['weekNumber'];
}
// annéee
if(empty($_GET['year'])) {
    $year = $dateTime->format('Y');
}else{
    $year = $_GET['year'];
}

// condition pour voir la weekly seed et pouvoir poster son temps
if((($dayNumber == 5 && $hourNumber>17) || $dayNumber == 6 || $dayNumber == 7 || $dayNumber == 1 || $dayNumber == 2 || $dayNumber == 3 || $dayNumber == 4 || ($dayNumber == 5 && $hourNumber<7))&&(isset($_SESSION['id']))){
    // recherche si un temps a été envoyé
    $sql        =   'SELECT timeSent FROM times WHERE fk_user_id='.$userID.' AND year='.$year.' AND week='.$weekNumber;
    $stmt       =   $db->prepare($sql);
    if($stmt->execute()){
        while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
            $oldTimeSent = $row['timeSent'];
        }
    }


    // contenu de la weekly seed
    if(!empty($_POST['time'])){
        // décrémentation du numéro de semaine si le lundi
        $result	=	0;
        // traitement de la requête
        $userTime =$_POST['time'];
        // effacement si temps précédent
        $sql 		=	'DELETE FROM times WHERE fk_user_id='.$userID.' AND year='.$year.' AND week='.$weekNumber;
        $stmt       =   $db->prepare($sql);
        if($stmt->execute()){
            while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
            }
        }
        // envoi à la table times
        $sql        =   "INSERT INTO times (fk_user_id, year, week, timeSent) VALUES (?,?,?,?)";
        $stmt       =   $db->prepare($sql);
        if($stmt->execute([$userID,$year,$weekNumber,$userTime])){
            $result++;
            $oldTimeSent = $userTime;
        }
        if($result==1){
            echo "<div>You time has been sent, thank you. </div>";
        }else{
            echo "<div>There was an error while sending your time. </div>";
        }
        if(date("N")=='1'){
            $weekNumber++;
        }
    }
    ?>
    <div><h3><a href="https://noobill.ch/RandoBlazer/build/weeklySeed.zip" target="_blank">Dowload weekly seed</a></h3></div>
    <form action="" method="post">
        <fieldset>
            <legend>Then you can post/update your time here for the <u><?php echo $year;?> week <?php echo $weekNumber;?>'s seed</u> : </legend>
            <div class="form-group">
                <label for="exampleInputEmail1">Your time</label>
                <input name="time" type="time" class="form-control" id="userTime" aria-describedby="timeHelp" step="1"
                    <?php
                    if(!empty($oldTimeSent))
                    {echo 'value="'.$oldTimeSent.'"';}
                    ?>
                >
                <small id="timeHelp" class="form-text text-muted">Please don't be a jerk, let us know what was your real time.</small>
            </div>
            <button type="submit" class="btn btn-primary">Submit</button>
        </fieldset>
    </form>
    <?php
}else{
    // pas contenu de la weekly seed -> résultats dernière weekly seed
    if($weekNumber==1){
        $lastWeekNumber = 53;
        $lastYearNumber = $year - 1;
    }else{
        $lastWeekNumber = $weekNumber - 1;
        $lastYearNumber = $year;
    }

    if($weekNumber==1){
        $pastWeekNumber = 53;
        $pastYearNumber = $year - 1;
    }else{
        $pastWeekNumber = $weekNumber - 1;
        $pastYearNumber = $year;
    }
    if($weekNumber==53){
        $futureWeekNumber = 1;
        $futureYear = $year + 1;
    }else{
        $futureWeekNumber = $weekNumber + 1;
        $futureYear = $year;
    }

    // recherche si temps postés la semaine précédente
    $sql        =   'SELECT id FROM times WHERE week='.$lastWeekNumber.' AND year='.$lastYearNumber;
    $stmt       =   $db->prepare($sql);
    $i 			=	0;
    if($stmt->execute()){
        while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
            $i++;
        }
    }
    if($i!=0){
        // classement semaine précédente
        if($getYear>-1) $year=$getYear;
        if($getWeekNumber>-1) $lastWeekNumber=$getWeekNumber;

        $sql        =   'SELECT user.id AS userID, user.username AS username,times.timeSent AS timeSent 
		FROM user INNER JOIN times ON user.id=times.fk_user_id 
		WHERE times.week='.$lastWeekNumber.' AND times.year='.$lastYearNumber.' ORDER by times.timeSent ASC';
        $stmt       =   $db->prepare($sql);
        $rank		= 	0;
        if($getWeekNumber==-1){
            echo "<h2>Last weekly seed results</h2>";
        }else{
            echo '<h2>Week '.$getWeekNumber.' ('.$getYear.') seed results</h2>';
        }

        echo "<table class='table' border='0'>";
        echo "<tr><thead><th scope='col'>Rank</th><th scope='col'>Player</th><th scope='col'>Time</th></thead></tr>";
        if($stmt->execute()){
            while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
                $rank++;
                $userTime = $row['timeSent'];

                echo'<tr><td>'.$rank.'</td><td><a href="profile.php?id='.$row['userID'].'">'.$row['username'].'</a></td><td>'.$userTime.'</td></tr>';
            }
        }
        echo "</table>";

        // buttons for previous week

        // chacking for highest week number i want to show (not the current week before monday 2pm cet/cest)
        // Traitement du temps
        $dateTime = new dateTime('', new DateTimeZone('Europe/Berlin'));
        // numéro de jour de semaine (vendredi 5, samedi 6, dimanche 7, lundi 1, etc...)
        $dayNumber = $dateTime->format('N');
        // heure de la journée
        $hourNumber = $dateTime->format('H');
        // numéro de semaine
        $weekNumber = $dateTime->format('W');
        // annéee
        $year = $dateTime->format('Y');
        if($dayNumber==1 && $hourNumber<14){
            $maxWeekNumber = $weekNumber - 1;
        }else{
            $maxWeekNumber = $weekNumber;
        }
        $maxYear = $year;

    }else{
        // pas de temps posté la semaine précédente
        echo "<div>Nobody posted a time last week.</div>";
    }
    // showing those buttons
    echo '<table class="table"><tr>';
    echo '<td><a href="weeklySeed.php?weekNumber='.$pastWeekNumber.'&year='.$pastYearNumber.'">Previous seed</a></td>';
    echo '<td><a href="weeklySeed.php?weekNumber='.$futureWeekNumber.'&year='.$futureYear.'">Following seed</a></td>';
    ?>
    <?php
}



?>

<?php
include('down.php');
?>