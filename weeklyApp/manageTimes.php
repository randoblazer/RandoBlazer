<?php
include('up.php');
// définition variable
if(!empty($_SESSION['is_admin'])){
    if($_SESSION['is_admin']==1){
        // traitement effacement
        if(isset($_POST['idToDelete'])){
            $idToDelete = $_POST['idToDelete'];
            $sql 		=	'DELETE FROM times WHERE id='.$idToDelete;
            $stmt       =   $db->prepare($sql);
            if($stmt->execute()){
                while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
                }
            }
        }
        // traitement envoi
        if(isset($_POST['userAdd'])&&isset($_POST['yearAdd'])&&isset($_POST['weekAdd'])&&isset($_POST['timeAdd'])){
            $userAdd    =   $_POST['userAdd'];
            $yearAdd    =   $_POST['yearAdd'];
            $weekAdd    =   $_POST['weekAdd'];
            $timeAdd    =   $_POST['timeAdd'];
            $timeAdd    =   '0000-00-00 '.$timeAdd;
            $sql        =   "INSERT INTO times (fk_user_id, year, week, timeSent) VALUES (?,?,?,?)";
            $stmt       =   $db->prepare($sql);
            if($stmt->execute([$userAdd,$yearAdd,$weekAdd,$timeAdd])){
                echo 'Time added';
            }
        }

        // traitement modifications
        if(isset($_POST['timeToUpdate'])&&isset($_POST['userToDelete'])&&isset($_POST['year'])&&isset($_POST['week'])&&isset($_POST['timeSent'])){
            $timeToUpdate   =   $_POST['timeToUpdate'];
            $userToDelete   =   $_POST['userToDelete'];
            $year           =   $_POST['year'];
            $week           =   $_POST['week'];
            $timeSent       =   $_POST['timeSent'];
            $timeSent       =   '0000-00-00 '.$timeSent;

            $sql        =   'UPDATE times SET fk_user_id='.$userToDelete.', year='.$year.', week='.$week.', timeSent="'.$timeSent.'" WHERE id='.$timeToUpdate;
            $stmt       =   $db->prepare($sql);
            if($stmt->execute()){
                while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {

                }
            }
            $stmt       =   $db->prepare($sql);
            if($stmt->execute()){
                while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {

                }
            }
        }
        // ajout de temps
        $sql        =   "SELECT id,username FROM user ORDER by username";
        $stmt       =   $db->prepare($sql);
        echo '<h3>Adding time</h3>';
        echo '<table class="table"><tr>';
        echo '<th>Nickname</th>';
        echo '<th>Year</th>';
        echo '<th>Week</th>';
        echo '<th>time</th>';
        echo '<th>Action</th>';
        echo '</tr>';

        echo '<tr>';
        echo '<form action="" method="post" id="addingTime">';
        echo '<td><select name="userAdd" autocomplete="off">';
        if($stmt->execute()){
            while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
                // nickname
                echo '<option value="'.$row["id"].'"';
                echo '>'.$row["username"].'</option>';
            }
        }
        echo '</select></td>';
        // year
        echo '<td><select name="yearAdd" autocomplete="off">';
        $sql1   = 'SELECT DISTINCT year FROM times ORDER by year';
        $stmt1  = $db->prepare($sql1);
        if($stmt1->execute()){
            while ($row1 = $stmt1->fetch(PDO::FETCH_ASSOC)){
                echo '<option value="'.$row1["year"].'"';
                echo '>'.$row1["year"].'</option>';
            }
        }
        echo '</select></td>';
        // week
        echo '<td><select name="weekAdd" autocomplete="off">';
        $sql1   = 'SELECT DISTINCT week FROM times ORDER by week';
        $stmt1  = $db->prepare($sql1);
        if($stmt1->execute()){
            while ($row1 = $stmt1->fetch(PDO::FETCH_ASSOC)){
                echo '<option value="'.$row1["week"].'"';
                echo '>'.$row1["week"].'</option>';
            }
        }
        echo '</select></td>';
        // time
        echo '<td><input type="time" step="1" name="timeAdd" min="01:00:00" max="20:00:00"></td>';
        // action
        echo '<td><button type="submit" class="btn btn-primary" form="addingTime" value="Submit">Add</button></td>';
        echo '</form>';
        echo '</tr>';
        echo '</table>';

        // affichage des temps
        $sql        =   "SELECT id,fk_user_id,year,week,timeSent FROM times order by year DESC, week DESC,timeSent DESC"; //
        $stmt       =   $db->prepare($sql);
        echo '<h3>Time posted</h3>';
        echo '<table class="table"><tr>';
        echo '<th>Nickname</th>';
        echo '<th>Year</th>';
        echo '<th>Week</th>';
        echo '<th>time</th>';
        echo '<th>Action</th>';
        echo '</tr>';
        $i = 0;
        if($stmt->execute()){
            while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
                echo '<tr>';

                echo '<tr>';


                echo '<form action="" method="post" id="form'.$i.'">';
                echo '<input name="timeToUpdate" type="hidden" value="'.$row["id"].'">';

                // nickname


                echo '<td><select name="userToDelete" autocomplete="off">';
                $sql1   = 'SELECT id,username FROM user ORDER by username';
                $stmt1  = $db->prepare($sql1);
                if($stmt1->execute()){
                    while ($row1 = $stmt1->fetch(PDO::FETCH_ASSOC)){
                        echo '<option value="'.$row1["id"].'"';
                        if($row1['id']==$row['fk_user_id']){
                            echo ' selected';
                        }
                        echo '>'.$row1["username"].'</option>';
                    }
                }
                echo '</select></td>';
                // year
                echo '<td><select name="year" autocomplete="off">';
                $sql1   = 'SELECT DISTINCT year FROM times ORDER by year';
                $stmt1  = $db->prepare($sql1);
                if($stmt1->execute()){
                    while ($row1 = $stmt1->fetch(PDO::FETCH_ASSOC)){
                        echo '<option value="'.$row1["year"].'"';
                        if($row1['year']==$row['year']){
                            echo ' selected';
                        }
                        echo '>'.$row1["year"].'</option>';
                    }
                }
                echo '</select></td>';
                // week
                echo '<td><select name="week" autocomplete="off">';
                $sql1   = 'SELECT DISTINCT week FROM times ORDER by week';
                $stmt1  = $db->prepare($sql1);
                if($stmt1->execute()){
                    while ($row1 = $stmt1->fetch(PDO::FETCH_ASSOC)){
                        echo '<option value="'.$row1["week"].'"';
                        if($row1['week']==$row['week']){
                            echo ' selected';
                        }
                        echo '>'.$row1["week"].'</option>';
                    }
                }
                echo '</select></td>';
                // time
                $thatTime = new DateTime($row["timeSent"]);
                $thatTimeShown = $thatTime->format('H:i:s');
                echo '<td><input type="time" step="1" name="timeSent" min="01:00:00" max="20:00:00" value="'.$thatTimeShown.'"></td>';

                echo '<td><button type="submit" class="btn btn-primary" form="form'.$i.'" value="Submit">Update</button>&nbsp;';
                echo '</form>';
                // Delete
                echo '<form action="" method="post" id="delete_'.$i.'">';
                echo '<input name="idToDelete" type="hidden" value="'.$row["id"].'">';
                echo '<button type="submit" class="btn btn-danger" form="delete_'.$i.'" value="Submit">Delete</button>';
                echo '</form>';
                echo '</td></tr>';
                $i++;
            }
        }

        ?>

        <?php
    }
}



include('down.php');
?>