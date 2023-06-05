<?php
// connaitre le rang d'un joueur pour une weekly seed spécifique
function weeklySeedUserRanking($userID, $year, $week, $db){
	$i 			=	0;
	$output		=	0;
	$sql        =   'SELECT fk_user_id FROM times WHERE year='.$year.' AND week='.$week.' ORDER BY timeSent ASC';
	$stmt       =   $db->prepare($sql);
	if($stmt->execute()){
		while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
			$i++;
			if($row['fk_user_id']==$userID){
				$output	=	$i;
			}
		}
	}
	return $output;			
}

?>