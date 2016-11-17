<?php

function content_type_export_all_entity_fields($build) {

  $entities_types = entity_get_info();

  // Loop entity types
  foreach($entities_types as $entity_type => $entities_type_details) {

    $build[$entity_type] = array(
      '#type' => 'fieldset',
      '#title' => $entity_type,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $build[$entity_type]['bundles'] = array(
      '#type' => 'container',
    );

    $build[$entity_type]['bundles']['label']['#markup'] = '<h3>' . t('Bundles') . '</h3>';

    // Loop bundles
    foreach($entities_type_details['bundles'] as $bundle_name => $bundle_details) {

      $build[$entity_type]['bundles']['children'][$bundle_name] = array(
        '#type' => 'fieldset',
        '#title' => $bundle_name,
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );

      $build[$entity_type]['bundles']['children'][$bundle_name]['fields'] = array(
        '#type' => 'textarea',
        '#title' => 'Fields',
        '#value' => content_type_export_dump_fields_as_code($bundle_name, $entity_type),
        '#resizable' => TRUE,
      );

      $build[$entity_type]['bundles']['children'][$bundle_name]['instances'] = array(
        '#type' => 'textarea',
        '#title' => 'Instances',
        '#value' => content_type_export_dump_instances_as_code($bundle_name, $entity_type),
        '#resizable' => TRUE,
      );

    }

  }

  return $build;

}
