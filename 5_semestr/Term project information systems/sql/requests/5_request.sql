SELECT idClient, SUM(Weight) FROM consignmentnote
WHERE YEAR(NoteDate) = $year
group by idClient