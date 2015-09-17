<?php
/**
 * @file
 * movie_import.drush.inc
 */

/*
 * Implements drush_command hook
 */

function movie_import_drush_command() {
    $items = array();

    $items['movie-bulk-import'] = array(
        'callback' => 'movie_import_bulk_import_movies',
        'description' => "Bulk imports 250 top films from IMDB",
        'examples' => array(
            'drush mi-b' => 'Bulk imports movies',
        ),
        'aliases' => array('mi-b'),
    );
    $items['movie-bulk-delete'] = array(
        'callback' => 'movie_import_bulk_delete_movies',
        'description' => "Bulk deletes 250 top films from IMDB",
        'examples' => array(
            'drush mi-d' => 'Bulk delete movies',
        ),
        'aliases' => array('mi-d'),
    );

    return $items;

}
/*
 * Bulk import function
 */
function movie_import_bulk_import_movies() {
    drupal_set_message(t('importing Movies'));
    $movie_titles = variable_get('movie_import_list');
    foreach ($movie_titles as $title) {
       $movie = movie_import_check_movie_valid($title);
        if ($movie) :
            movie_import_save_movie($movie);
        endif;
    }

}
/*
 * Bulk delete function
 */
function movie_import_bulk_delete_movies() {
    drupal_set_message(t('deleting movies reviews'));

    // Get all nodes by the content type of reviews
    $nodes = db_select("node", 'n')
        ->fields('n', array('nid'))
        ->condition('type', 'movie_review')
        ->condition('status', 1)
        ->orderBy('created', 'ASC')
        ->execute()->fetchCol();

    if ($nodes) :
        node_delete_multiple($nodes);
    endif;

    drupal_set_message( t('Success! All movie reviews have been deleted.') );
}