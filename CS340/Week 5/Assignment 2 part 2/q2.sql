SELECT c.name AS category_name, 
COUNT(a.actor_id) AS number_of_films from category c
LEFT JOIN film_category fc ON fc.category_id = c.category_id
LEFT JOIN film f ON f.film_id = fc.film_id
LEFT JOIN film_actor fa ON fa.film_id = f.film_id
LEFT JOIN actor a ON a.actor_id = fa.actor_id and a.first_name LIKE 'ED' and a.last_name LIKE 'CHASE'
GROUP BY category_name
ORDER BY category_name ASC