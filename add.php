<?php
  include('koneksi.php');

  $sensor = $_GET['suhu_air'];

  $sql = "INSERT INTO tbl_water (suhu_air) VALUES (:suhu_air)";

  $stmt - $PDO->prepare($sql);

  $stmt->bindParam(':suhu_air', $sensor);

  if (stmt->execute()) {
    echo "sukses gaees!";
  } else {
    echo "gagal kirim nih";
  }
?>