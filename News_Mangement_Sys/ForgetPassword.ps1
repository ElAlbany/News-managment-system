$smtpServer = "smtp.gmail.com"
$smtpPort = 587
$emailFrom = "newsmanegmentsystem@gmail.com"
$emailTo = "
$subject = "News Account Password"
$body = "your random genrated code is 
$password = ConvertTo-SecureString "pygq khev sgje iihl" -AsPlainText -Force
$credential = New-Object System.Management.Automation.PSCredential ($emailFrom, $password)
$mailMessage = New-Object System.Net.Mail.MailMessage
$mailMessage.Subject = $subject
$mailMessage.Body = $body
$mailMessage.From = $emailFrom
$mailMessage.To.Add($emailTo)
$smtpClient = New-Object System.Net.Mail.SmtpClient($smtpServer, $smtpPort)
$smtpClient.EnableSsl = $true
$smtpClient.Credentials = $credential
#Sending email
$smtpClient.Send($mailMessage)