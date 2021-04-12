SELECT month(NoteDate), avg(Weight)
FROM consignmentnote
WHERE year(NoteDate) = 2013
GROUP BY month(NoteDate)