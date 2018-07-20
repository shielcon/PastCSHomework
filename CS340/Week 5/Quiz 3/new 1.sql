SELECT bp.name as name, count(bcp.pid) as CertCount
FROM bsg_cert_people bcp 
inner JOIN bsg_people p ON p.id = bcp.pid
inner JOIN bsg_planets bp ON bp.id = p.homeworld
GROUP BY bp.name;

SELECT DISTINCT fname, lname FROM bsg_people p
INNER JOIN bsg_ship_assignment bsa ON bsa.pid = p.id
INNER JOIN bsg_ship_instance bsi ON bsi.id = bsa.sid
INNER JOIN bsg_ship_class bsc ON bsc.id = bsi.class 
AND bsc.name LIKE 'VIPER'
ORDER BY p.fname;

SELECT fname, lname, bsi.id AS ship_instance_id FROM bsg_people p
INNER JOIN bsg_ship_assignment bsa ON bsa.pid = p.id
INNER JOIN bsg_ship_instance bsi ON bsi.id = bsa.sid
INNER JOIN bsg_ship_class bsc ON bsc.id = bsi.class 
AND bsc.name LIKE 'VIPER'
WHERE p.id NOT IN 
(SELECT bcp.pid FROM bsg_cert_people bcp
INNER JOIN bsg_cert bc ON bc.id = bcp.cid
AND bc.title LIKE 'Viper')
ORDER BY p.fname