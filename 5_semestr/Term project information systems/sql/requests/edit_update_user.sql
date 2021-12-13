UPDATE labs.groupaccess
SET Login       = '$Login',
    Password    = '$Password',
    AccessLevel = $AccessLevel
WHERE idGroup = $idGroup