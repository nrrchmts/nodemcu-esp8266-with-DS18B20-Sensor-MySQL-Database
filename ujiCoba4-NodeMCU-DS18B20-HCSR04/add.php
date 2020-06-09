<?php
include('koneksi.php');

$sensor = $_GET['suhu_air'];
$sensor2 = $_GET['volume_air'];

$sql = "INSERT INTO sektor (suhu_air, volume_air) VALUES(:suhu, :volume)";

$stmt = $PDO->prepare($sql);

$stmt->bindParam(':suhu', $sensor);
$stmt->bindParam(':volume', $sensor2);

if ($stmt->execute()) {
    echo "sukses gaes";
} else {
    echo "gagal gaes";
}
