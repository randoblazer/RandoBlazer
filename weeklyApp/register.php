<?php
include('up.php');

if(isset($_POST['username']) && isset($_POST['twitch']) && isset($_POST['password']) && isset($_POST['password2']) && isset($_POST['location']) && isset($_POST['gender']) ){
    // variable names recovery
    $username       =   $_POST['username'];
    $twitch         =   $_POST['twitch'];
    $password       =   $_POST['password'];
    $password2      =   $_POST['password2'];
    $word           =   password_hash($password, PASSWORD_ARGON2ID);
	$location      	=   addslashes($_POST['location']);
	$birthday     	=   $_POST['birthday'];
	if(empty($birthday)){
		$birthday 	=	"0000-00-00";
	}
	$gender 	    =   $_POST['gender'];
	$comment 		=	addslashes($_POST['comment']);
    $result         =   0;
    $errors         =   0;
    
    // controlling datas
    // username
    if (!preg_match("/^[a-zA-Z0-9\-\_' éàèôûùî]*$/",$username)) {
        $usernameErr = "Format is not valid";
        $errors++;
    }
    // contrôle si le pseudo est déjà pris
    $i 		=	0;
    $sql    =   'SELECT id FROM user WHERE username="'.$username.'"';
    $stmt   =   $db->prepare($sql);
    if($stmt->execute()){
    	while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
    		$i++;
    	}
    }
    if ($i>0){
        $usernameErr2 = "This username is already used";
        $errors++;
    }

    // twitch
    if (!preg_match("/^[a-zA-Z0-9\-\_' éàèôûùî]*$/",$twitch)) {
        $twitchErr = "le format est invalide";
        $errors++;
    }
    // password
    if ($password != $password2) {
        $passwordErr = "You must enter the same password twice";
        $errors++;
    }
    
    // sortie de la boucle en cas d'erreur de format
    if($errors===0){
        $result = 1;
        if($result===1){
            // worker line cration on workers tab
            $sql        =   "INSERT INTO user (username, password, location, gender, birthday, twitch, comment) VALUES (?,?,?,?,?,?,?)";
            $stmt       =   $db->prepare($sql);
            if($stmt->execute([$username,$word,$location,$gender,$birthday,$twitch,$comment])){
                $result++;
            }
            unset($_POST);
            // message de réussite ou redirection
            header('Location: weeklySeed.php');
        }else{
           echo '<p>Une erreur est survenue, prière de modifier les champs nécessaires</p>'; 
        }
    }
}

?>
<form method="post" id="registerForm">
	<div class="form-row">
		<div class="form-group col-md-6">
			<label>Username</label>
			<input type="text" name="username" class="form-control" <?php if(!empty($_POST['username'])){echo 'value="'.$_POST["username"].'"';}?> required />
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
			<input type="text" name="twitch" class="form-control" <?php if(!empty($_POST['twitch'])){echo 'value="'.$_POST["twitch"].'"';}?> required />
			<?php
			if(isset($twitchErr)){
				echo '&nbsp;<font color="red">'.$twitchErr.'</font>';
			}
			?>
		</div>
	</div>
	<div class="form-row">
		<div class="form-group col-md-6">
			<label>Password</label>
			<input type="password" name="password" class="form-control" <?php if(!empty($_POST['password'])){echo 'value="'.$_POST["password"].'"';}?> required />
			<?php
			if(isset($passwordErr)){
				echo '&nbsp;<font color="red">'.$passwordErr.'</font>';
			}
			?>
		</div>
		<div class="form-group col-md-6">
			<label>Password</label>
			<input type="password" name="password2" class="form-control" <?php if(!empty($_POST['password2'])){echo 'value="'.$_POST["password2"].'"';}?> required />
		</div>
	</div>
	<div class="form-row">
		<div class="form-group col-md-6">
			<label>Location</label>
			<input type="text" name="location" class="form-control" placeholder="City, country/state"<?php if(!empty($_POST['location'])){echo 'value="'.$_POST["location"].'"';}?> />
			<?php
			if(isset($locationErr)){
				echo '&nbsp;<font color="red">'.$locationErr.'</font>';
			}
			?>
		</div>
		<div class="form-group col-md-6">
			<label>Birthday</label>
			<input type="date" name="birthday" class="form-control" <?php if(!empty($_POST['birthday'])){echo 'value="'.$_POST["birthday"].'"';}else{echo 'value="0000-00-00"';}?>  />
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
			<option value="1">Female</option>
			<option value="2">Male</option>
			<option value="3">Other</option>
			<option value="4">not specified</option>
			</select>
		</div>
	</div>

	<div class="form-row">
		<div class="form-group col-md-12">
			<label>Biography</label>
			<textarea class="form-control" name="comment" rows="3"><?php if(!empty($_POST['comment'])){echo '.$_POST["comment"]';}?></textarea>
			<?php
			if(isset($commentErr)){
				echo '&nbsp;<font color="red">'.$commentErr.'</font>';
			}
			?>
		</div>
	</div>

	<div class="form-row">
		<div class="form-group col-md">
			<!--
			<button type="submit" class="btn btn-primary">Register</button>
			-->
			<button class="g-recaptcha btn btn-primary" 
        data-sitekey="6LcNyV8bAAAAAI9y2NT3bUyCOc226MPQ9oy-84q5" 
        data-callback='onSubmit' 
        data-action='submit' >Register</button>

		</div>
	</div>
</form>

<?php
include('down.php');
?>