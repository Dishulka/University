SELECT * FROM employee
WHERE TO_DAYS(CURDATE()) - TO_DAYS(HiredDate) < $hiredDays