/*SELECT a.first_name, a.last_name, sciFiActors.total_combined_film_length FROM actor a
LEFT JOIN 
    (SELECT a.first_name, a.last_name, a.actor_id, SUM( f.length ) AS total_combined_film_length, c.name
    FROM actor a
	INNER JOIN film_actor fa ON fa.actor_id = a.actor_id
	INNER JOIN film f on f.film_id = fa.film_id
	INNER JOIN film_category fc ON fc.film_id = f.film_id
	INNER JOIN category c on c.category_id = fc.category_id
     AND c.name LIKE 'Sci-Fi'
    GROUP BY a.actor_id) 
    AS sciFiActors
ON a.actor_id = sciFiActors.actor_id;*/

SELECT a.first_name, a.last_name, IFNULL(sciFiA.total_combined_film_length, 0)
FROM actor a
LEFT JOIN 
    (SELECT a.first_name, a.last_name, a.actor_id, SUM( f.length) AS total_combined_film_length, c.name
    FROM actor a, film_actor fa, film f, film_category fc, category c
    WHERE c.category_id = fc.category_id
    AND fc.film_id = f.film_id
    AND a.actor_id = fa.actor_id
    AND fa.film_id = f.film_id
    AND c.name =  'Sci-Fi'
    GROUP BY a.actor_id) 
    AS sciFiA 
ON a.actor_id = sciFiA.actor_id
ORDER BY a.actor_id;