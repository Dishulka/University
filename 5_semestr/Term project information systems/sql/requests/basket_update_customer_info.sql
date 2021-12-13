UPDATE customer
SET TotalWeight     = $weight,
    DateTotalWeight = CURRENT_DATE()
WHERE idClient = $idClient