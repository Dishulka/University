SELECT MONTH(NoteDate), COUNT(idConsignmentNote)
FROM consignmentnote
WHERE YEAR(NoteDate) = $year
group by MONTH(NoteDate)