SELECT bp.name as name, count(DISTINCT bcp.pid) as CertCount
FROM bsg_cert_people bcp 
left JOIN bsg_people p ON p.id = bcp.pid
LEFT JOIN bsg_planets bp ON bp.id = p.homeworld
GROUP BY bp.name
HAVING COUNT(bcp.pid) > 0