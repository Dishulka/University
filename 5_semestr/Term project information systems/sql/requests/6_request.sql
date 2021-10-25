SELECT MONTH(NoteDate), AVG(Weight)
FROM consignmentnote
WHERE YEAR(NoteDate) = $year
GROUP BY MONTH(NoteDate)