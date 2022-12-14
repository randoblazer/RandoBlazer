<?php
include('up.php');
// définition variable
if(!empty($_SESSION['is_admin'])){
    if($_SESSION['is_admin']==1){
        //// traitements
        /// Ajout admin
        if(isset($_POST['userToAdd'])){
            $userToAdd = $_POST['userToAdd'];
            $sql        =   'UPDATE user SET is_admin="1" WHERE id='.$userToAdd;
            $stmt       =   $db->prepare($sql);
            if($stmt->execute()){
                while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {

                }
            }
        }

        /// Suppression admin
        if(isset($_POST['userToDelete'])){
            $userToDelete = $_POST['userToDelete'];
            $sql        =   'UPDATE user SET is_admin="0" WHERE id='.$userToDelete;
            $stmt       =   $db->prepare($sql);
            if($stmt->execute()){
                while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {

                }
            }
        }

        // liste admins
        $sql        =   "SELECT username FROM user WHERE is_admin='1'";
        $stmt       =   $db->prepare($sql);
        $i 			=	0;
        echo '<h3>Admin users list</h3>';
        echo '<table class="table"><tr>';
        echo '<th>Nickname</th></tr>';
        if($stmt->execute()){
            while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
                echo '<tr><td>'.$row["username"].'</td></tr>';
                $i++;
            }
        }
        echo '</table>';

        // ajout admin
        echo '<h3>Adding new admin</h3>';
        echo '<form action="" method="post">';
        $sql        =   "SELECT id,username FROM user WHERE is_admin='0' ORDER BY username";
        $stmt       =   $db->prepare($sql);
        echo '<select name="userToAdd">';
        if($stmt->execute()){
            while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
                echo '<option value="'.$row["id"].'">'.$row["username"].'</option>';
            }
        }
        echo '</select>&nbsp;';
        echo '<button type="submit" class="btn btn-primary">Add an admin</button>';
        echo '</form>';

        // deleting admin
        echo '<h3>Deleting admins</h3>';
        echo '<form action="" method="post">';
        $sql        =   "SELECT id,username FROM user WHERE is_admin='1' AND id!=".$_SESSION['id']." ORDER BY username";
        $stmt       =   $db->prepare($sql);
        echo '<select name="userToDelete">';
        if($stmt->execute()){
            while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
                echo '<option value="'.$row["id"].'">'.$row["username"].'</option>';
            }
        }
        echo '</select>&nbsp;';
        echo '<button type="submit" class="btn btn-primary">Delete this admin</button>';
        echo '</form>';
        ?>







        <?php
    }
}



include('down.php');
?>