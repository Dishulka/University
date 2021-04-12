SELECT MONTH(NoteDate), count(idConsignmentNote)
FROM consignmentnote
WHERE YEAR(NoteDate)=2013
group by MONTH(NoteDate)