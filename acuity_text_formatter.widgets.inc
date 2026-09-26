<?php

/**
 * Implements hook_field_widget_info().
 */
function acuity_text_formatter_field_widget_info() {
  return [
    'acuity_text_formatter_widget' => [
      'label' => t('Acuity Text Formatter'),
      'field types' => ['text', 'text_long', 'text_with_summary', 'email'],
      'settings' => [
        'acuity_formatter_settings' => [
          'trim' => 0,
          'case_transform' => 'none',
        ],
      ],
      'module' => 'acuity_text_formatter',
    ],
  ];
}

/**
 * Implements hook_field_widget_settings_form().
 */
function acuity_text_formatter_field_widget_settings_form($field, $instance) {
  $settings = $instance['widget']['settings'];
  $defaults = isset($settings['acuity_formatter_settings']) ? $settings['acuity_formatter_settings'] : [];

  $form['acuity_formatter_settings'] = [
    '#type' => 'fieldset',
    '#title' => t('Text Formatting'),
    '#description' => t('Configure how text is automatically formatted when saved.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  ];

  $form['acuity_formatter_settings']['trim'] = [
    '#type' => 'checkbox',
    '#title' => t('Trim leading/trailing spaces'),
    '#default_value' => isset($defaults['trim']) ? $defaults['trim'] : 0,
  ];

  $case_options = [
    'none' => t('- None -'),
    'lowercase' => t('Convert to lowercase'),
    'uppercase' => t('Convert to uppercase'),
    'camelcase' => t('CamelCase'),
    'intercapped' => t('Intercapped (e.g., McCallister, O\'Connor)'),
  ];

  // Only lowercasing means anything for an email address; the other modes
  // would mangle it.
  $is_email = $field['type'] === 'email';
  if ($is_email) {
    $case_options = array_intersect_key($case_options, array_flip(['none', 'lowercase']));
  }

  $default_case = isset($defaults['case_transform']) ? $defaults['case_transform'] : 'none';

  $form['acuity_formatter_settings']['case_transform'] = [
    '#type' => 'select',
    '#title' => t('Case Transformation'),
    '#description' => $is_email
      ? t('Lowercasing keeps addresses consistent and makes duplicates easy to find. Existing values are only changed when next saved.')
      : t('Select a case transformation to apply on save.'),
    '#options' => $case_options,
    '#default_value' => isset($case_options[$default_case]) ? $default_case : 'none',
  ];

  return $form;
}

/**
 * Implements hook_field_widget_settings_summary().
 */
function acuity_text_formatter_field_widget_settings_summary($field, $instance) {
  $settings = $instance['widget']['settings'];
  $format_settings = isset($settings['acuity_formatter_settings']) ? $settings['acuity_formatter_settings'] : [];
  $summary = [];

  if (!empty($format_settings['trim'])) {
    $summary[] = t('Trim: Yes');
  }

  if (!empty($format_settings['case_transform']) && $format_settings['case_transform'] !== 'none') {
    $labels = [
      'lowercase' => t('Lowercase'),
      'uppercase' => t('Uppercase'),
      'camelcase' => t('CamelCase'),
      'intercapped' => t('Intercapped'),
    ];
    $label = isset($labels[$format_settings['case_transform']]) ? $labels[$format_settings['case_transform']] : $format_settings['case_transform'];
    $summary[] = t('Case: @mode', ['@mode' => $label]);
  }

  if (empty($summary)) {
    $summary[] = t('No formatting enabled');
  }
  return $summary;
}

/**
 * Implements hook_field_widget_form().
 *
 * Text fields get a textfield or textarea on the 'value' column. Email fields
 * mirror core's email_field_widget_form(): the 'email' column and an HTML5
 * email input, so only the save-time formatting differs from core's widget.
 */
function acuity_text_formatter_field_widget_form($form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  if ($field['type'] === 'email') {
    $element['email'] = $element + [
      '#type' => 'email',
      '#default_value' => isset($items[$delta]['email']) ? $items[$delta]['email'] : NULL,
      '#size' => 60,
    ];
    return $element;
  }

  $value = isset($items[$delta]['value']) ? $items[$delta]['value'] : '';

  // Determine if this should be a textfield (single line) or textarea (multi-line)
  // based on the underlying field type.
  $is_long = in_array($field['type'], ['text_long', 'text_with_summary']);
  $widget_type = $is_long ? 'textarea' : 'textfield';

  $element['value'] = [
    '#type' => $widget_type,
    // CRITICAL FIX: Pass the title, description, and required status from the
    // parent $element to this child input, otherwise the label disappears.
    '#title' => $element['#title'],
    '#description' => $element['#description'],
    '#required' => $element['#required'],

    '#default_value' => $value,
    '#attributes' => ['class' => ['text-full']],
  ];

  // Type-specific properties
  if ($is_long) {
    $element['value']['#rows'] = !empty($instance['widget']['settings']['rows']) ? $instance['widget']['settings']['rows'] : 5;
  } else {
    $element['value']['#size'] = 60;
    $element['value']['#maxlength'] = !empty($field['settings']['max_length']) ? $field['settings']['max_length'] : 255;
  }

  return $element;
}