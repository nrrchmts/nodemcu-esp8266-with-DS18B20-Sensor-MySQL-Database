<?php
  include('koneksi.php');

  $sensor = $_GET['suhu_air'];

  $sql = "INSERT INTO sektor (suhu_air) VALUES(:suhu_air)";

  $stmt = $PDO->prepare($sql);

  $stmt->bindParam(':suhu_air', $sensor);

  if($stmt->execute()) {
      echo "sukses gaes";
  }else{
      echo "gagal gaes";
  }
