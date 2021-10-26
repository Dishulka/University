SELECT orders.idOrder, orders.NameCustomer, orders.contactInfo FROM orders
LEFT JOIN worksinorder using(idOrder)
LEFT JOIN services using(idService)
WHERE services.Name = '$NameService'