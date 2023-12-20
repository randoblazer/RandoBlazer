<?php
include('up.php');

// Traitement du temps
$dateTime = new dateTime('', new DateTimeZone('America/Los_Angeles'));
// numéro de jour de semaine (vendredi 5, samedi 6, dimanche 7, lundi 1, etc...)
$dayNumber = $dateTime->format('N');
// heure de la journée
$hourNumber = $dateTime->format('H');

if(!empty($_SESSION['id'])){
    $userID = $_SESSION['id'];
}
if(empty($_GET['year'])){
    $getYear = -1;
    $year = $dateTime->format('Y');
}else{
    $getYear = $_GET['year'];
    $year = $getYear;
}
if(empty($_GET['weekNumber'])){
    $getWeekNumber = -1;
    $weekNumber = $dateTime->format('W');
    if($dayNumber < 5 || ($dayNumber == 5 && $hourNumber < 8)) {
        $weekNumber = intval($weekNumber)-1;
        if ($weekNumber == 0) {
            $weekNumber = 53;
            $year--;
        }
    }
}else{
    $getWeekNumber = $_GET['weekNumber'];
    $weekNumber = $getWeekNumber;
}

$sql        =   'SELECT seed FROM weekly_seeds WHERE year='.$year.' AND week='.$weekNumber;
$stmt       =   $db->prepare($sql);
$seed = -1;
if($stmt->execute()){
    while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
        $seed = $row['seed'];
        $seedLink = 'https://randoblazer.com?race=1&seed='.$seed.'&note=weekly-'.$year.'-'.$weekNumber;
    }
}
if($seed != -1) {
?>
<h3>The weekly seed for
    <b><?php echo $year;?> week <?php echo $weekNumber;?></b> is
    <a href="<?php echo $seedLink;?>" target="_blank"><?php echo $seed;?></a>
</h3>
<h3 class="mb-4">
    <a href="<?php echo $seedLink;?>" target="_blank"><?php echo $seedLink;?></a>
</h3>
<?php
}

// condition pour voir la weekly seed et pouvoir poster son temps
// If we are logged in and not browsing to past weeks then show the time submission form
if(isset($_SESSION['id']) && $getWeekNumber == -1){
    // recherche si un temps a été envoyé
    $sql        =   'SELECT timeSent FROM times WHERE fk_user_id='.$userID.' AND year='.$year.' AND week='.$weekNumber;
    $stmt       =   $db->prepare($sql);
    if($stmt->execute()){
        while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
            $oldTimeSent = $row['timeSent'];
            $hms = explode(':', $oldTimeSent);
            $oldTimeHours = ltrim($hms[0], "0");
            $oldTimeMin = $hms[1];
            $oldTimeSec = $hms[2];
        }
    }

    // contenu de la weekly seed
    if(!empty($_POST['timehours']) && !empty($_POST['timemin']) && !empty($_POST['timesec'])){
        // décrémentation du numéro de semaine si le lundi
        $result	=	0;
        // traitement de la requête
        $userTime = $_POST['timehours'].':'.$_POST['timemin'].':'.$_POST['timesec'];
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
            $hms = explode(':', $oldTimeSent);
            $oldTimeHours = ltrim($hms[0], "0");
            $oldTimeMin = $hms[1];
            $oldTimeSec = $hms[2];
        }
        if($result==1){
            echo "<div>Your time has been sent, thank you. </div>";
        }else{
            echo "<div>There was an error while sending your time. </div>";
        }
        if(date("N")=='1'){
            $weekNumber++;
        }
    }
    ?>
    <form action="" method="post">
        <fieldset>
            <div class="form-row">
            <label>Your time</label>
            </div>
            <div class="form-row align-items-center">
                <input name="timehours" class="form-control" id="userTimeHours" aria-describedby="timeHelp"
                    pattern="\d" maxlength="1" style="width:3rem;text-align:right"
                    <?php
                    if(!empty($oldTimeSent))
                    {echo 'value="'.$oldTimeHours.'"';}
                    ?>
                >
                <label class="mx-2 align-middle" style="font-size:1em">:</label>
                <input name="timemin" class="form-control" id="userTimeMinutes" aria-describedby="timeHelp"
                    pattern="\d\d" maxlength="2" style="width:3rem"
                    <?php
                    if(!empty($oldTimeSent))
                    {echo 'value="'.$oldTimeMin.'"';}
                    ?>
                >
                <label class="mx-2 align-middle" style="font-size:1em">:</label>
                <input name="timesec" class="form-control" id="userTimeSeconds" aria-describedby="timeHelp"
                    pattern="\d\d" maxlength="2" style="width:3rem"
                    <?php
                    if(!empty($oldTimeSent))
                    {echo 'value="'.$oldTimeSec.'"';}
                    ?>
                >
            </div>
            <div class="form-row mb-2">
                <small id="timeHelp" class="form-text text-muted">Please don't be a jerk, let us know what was your real time.</small>
            </div>
            <div class="form-row">
                <button type="submit" class="btn btn-primary mb-3">Submit</button>
            </div>
        </fieldset>
    </form>
    <?php
} else {
    // Otherwise just give a link to the seed here

}

// Show all the times for this week if either we are not logged in or we are logged in and have submitted a time
// Or if we are browsing past weeks
if (!isset($_SESSION['id']) || !empty($oldTimeSent) || $getWeekNumber > -1) {
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
    $sql        =   'SELECT id FROM times WHERE week='.$weekNumber.' AND year='.$year;
    $stmt       =   $db->prepare($sql);
    $numTimes	=	0;
    if($stmt->execute()){
        while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
            $numTimes++;
        }
    }
    if($numTimes!=0){
        $sql        =   'SELECT user.id AS userID, user.username AS username,times.timeSent AS timeSent 
		FROM user INNER JOIN times ON user.id=times.fk_user_id 
		WHERE times.week='.$weekNumber.' AND times.year='.$year.' ORDER by times.timeSent ASC';
        $stmt       =   $db->prepare($sql);
        $rank		= 	0;
        if($getWeekNumber==-1){
            echo "<h2>Current weekly seed results (".$year." Week ".$weekNumber.")</h2>";
        }else{
            echo '<h2>'.$getYear.' Week '.$getWeekNumber.' results</h2>';
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