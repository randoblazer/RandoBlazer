<?php
include 'functions.php';
// mode débogueur
error_reporting(E_ALL);
ini_set('display_errors', 'On');
// déclaration des variables de l'application
define("PAGESCRIPT",            'index.php');               // page d'accueil de l'app
define("SERVERNAME",            'localhost');               // host de la base de données
define("DBUSERNAME",            'admin_netanonima');        // identifiant de la base de données
define("DBPASSWORD",            'Dlt3qyby44');              // mot de pass de la base de données
define("DBNAME",                'admin_randoblazer');       // nom de la base de données
define("YEAROFCREATION",        '2020');                    // année de la création de l'application

// connection à la base de donnée mysql
$db = new PDO('mysql:host='.SERVERNAME.'; dbname='.DBNAME, DBUSERNAME, DBPASSWORD, array (PDO::MYSQL_ATTR_INIT_COMMAND => 'SET NAMES \'UTF8\''));

// ouverture de session à chaque début de page
session_start();
// déconnexion
if(!empty($_GET['nav'])){
    if($_GET['nav']==='logout'){
        session_unset();
        session_destroy();
        // unset cookies
        if (isset($_SERVER['HTTP_COOKIE'])) {
            $cookies = explode(';', $_SERVER['HTTP_COOKIE']);
            foreach($cookies as $cookie){
                $parts = explode('=', $cookie);
                $name = trim($parts[0]);
                if($name!='darkMode'){
                    setcookie($name, '', time()-1000);
                    setcookie($name, '', time()-1000, '/');
                }
            }
        }   
        ?><script>location.href = "index.php?nav=login"</script><?php
    }
}
// redirection vers la page d'authentification si l'utilisateur n'est pas identifié
/*
if(!empty($_GET['nav'])){
    if(empty($_SESSION['username']) && $_GET['nav']!='login'){
        ?><script>location.href = "index.php?nav=login"</script><?php
    }
}else{
    if(empty($_SESSION['username'])){
        ?><script>location.href = "index.php?nav=login"</script><?php
    }
}
*/

// mise en forme des dates en français
    setlocale (LC_TIME, 'en_EN.UTF-8','en');
?>