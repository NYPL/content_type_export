<?php

/**
 * Attempts to output PHP code which can re-create a vocabulary for use in a module.
 */
function taxonomy_vocabulary_export_task($vocabulary) {
  $content = array();
  $content['bundle_export'] = array(
    '#type' => 'textarea',
    '#title' => 'Content type',
    '#value' => content_type_export_dump_taxonomy_vocabulary_as_code($vocabulary),
    '#resizable' => true,
  );
  $content['fields_export'] = array(
    '#type' => 'textarea',
    '#title' => 'Fields',
    '#value' => content_type_export_dump_fields_as_code($vocabulary->machine_name, 'taxonomy_term'),
    '#resizable' => true,
  );
  $content['instances_export'] = array(
    '#type' => 'textarea',
    '#title' => 'Instances',
    '#value' => content_type_export_dump_instances_as_code($vocabulary->machine_name, 'taxonomy_term'),
    '#resizable' => true,
  );
  $content['uninstall'] = array(
    '#type' => 'textarea',
    '#title' => 'Uninstall code',
    '#value' => content_type_export_taxonomy_uninstall_code($vocabulary->machine_name),
    '#resizable' => true,
  );
  $content['whole_install_file'] = array(
    '#type' => 'textarea',
    '#title' => 'The whole module.install',
    '#value' => content_type_export_install_file($content),
    '#resizable' => true,
    '#attributes' => array(
      'style' => 'height: 500px'
    ),
  );
  return $content;
}

/**
 * Export the basic properties needed to create a new taxonomy vocabulary in a module.
 */
function content_type_export_dump_taxonomy_vocabulary_as_code($vocabulary) {
  $export = "\$vocabulary = (object) array(
    'name' => '{$vocabulary->name}',
    'description' => '{$vocabulary->description}',
    'machine_name' => '{$vocabulary->machine_name}',
  );
  if(!taxonomy_vocabulary_machine_name_load(\$vocabulary->machine_name)) {
    taxonomy_vocabulary_save(\$vocabulary);
  }";
  return $export;
}

/**
 * Generate code for the uninstall hook
 */
function content_type_export_taxonomy_uninstall_code($machine_name) {
  $entity_type = 'taxonomy';
  $export = <<<PHP
  \$vocabulary = taxonomy_vocabulary_machine_name_load('$machine_name');
  taxonomy_vocabulary_delete(\$vocabulary->vid);
PHP;
  return $export;
}

