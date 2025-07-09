<?php
// Aktifkan penanganan error
error_reporting(E_ALL);
ini_set('display_errors', 1);

// Ambil data dari form login
$username = $_POST['username']; // HARUSNYA 'username', bukan 'admin'
$password = $_POST['password']; // HARUSNYA 'password', bukan '12345'

// Cek login
if ($username === 'admin' && $password === 'admin') {
    // Redirect ke home jika login berhasil
    header('Location: index.html');
    exit;
} else {
    echo "<h2>Login Gagal!</h2>";
    echo "<p>Username atau password salah.</p>";
}
?>
