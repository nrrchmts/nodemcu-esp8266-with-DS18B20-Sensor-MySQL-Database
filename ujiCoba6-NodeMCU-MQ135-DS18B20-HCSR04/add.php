<?php
include('koneksi.php');

$sensor = $_GET['suhu_air'];
$sensor2 = $_GET['volume_air'];
$sensor3 = $_GET['amoniak'];

$sql = "INSERT INTO sektor (suhu_air, volume_air, amoniak) VALUES(:suhu, :volume, :amonia)";

$stmt = $PDO->prepare($sql);

$stmt->bindParam(':suhu', $sensor);
$stmt->bindParam(':volume', $sensor2);
$stmt->bindParam(':amonia', $sensor3);

if ($stmt->execute()) {
    echo "sukses gaes";
} else {
    echo "gagal gaes";
}
