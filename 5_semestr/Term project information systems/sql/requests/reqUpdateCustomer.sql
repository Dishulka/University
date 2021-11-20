UPDATE customer
SET Name = '$Name',
    Adress   = '$Adress',
    TotalWeight = $TotalWeight,
    DateTotalWeight = '$DateTotalWeight'
WHERE idClient = $idClient