<?php
include('up.php');
if(!empty($_POST['username']) || !empty($_POST['password'])){
	// traitement de la tentative de connexion
	if(isset($_POST['username']) && isset($_POST['password'])){
    $username       =   $_POST['username'];
    $password       =   $_POST['password'];
    $stmt           =   $db->prepare("SELECT id,password,is_admin FROM user WHERE username=?");
    $stmt->bindParam(1, $username);
    $stmt->execute();
    $data           =   $stmt->fetch();
    if(isset($data['id'])){
        $userId         =   $data['id'];
        $hashpass       =   $data['password'];
        $verify         =   password_verify($password, $hashpass);
        if($verify){        
        // session creation
        $_SESSION['id']     	=   $userId;
        $_SESSION['username']  	=   $username;
        $_SESSION['is_admin'] = 0;
        if(isset($data['is_admin'])){
            if($data['is_admin']==1){
                $_SESSION['is_admin'] = 1;
            }
        }
        header('Location: index.php');
    }else{
        echo "<div class='panel panel-danger'>Le mot de passe est erroné</div>";
    }
    }else{
        echo "<div class='panel panel-danger'>L'identifiant est erroné</div>";
    }
}
}
?>
<h2>Login</h2>
<form action="" method="post">
  <fieldset>
    <div class="form-group">
      <label for="exampleInputEmail1">Username</label>
      <input name="username" type="text" class="form-control" id="username" maxlength="50">
    </div>
    <div class="form-group">
      <label for="exampleInputEmail1">Password</label>
      <input name="password" type="password" class="form-control" id="password" maxlength="60">
    </div>
    <button type="submit" class="btn btn-primary">Submit</button>
  </fieldset>
</form>

<?php
include('down.php');
?>