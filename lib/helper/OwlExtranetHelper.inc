<?php

/* vim: set syn=php expandtab tabstop=4 shiftwidth=4 softtabstop=4: */

/**																			 
 *  ,_,  
 * (o,o) 
 * {`"'}   OWL (Open Web Library)
 * -"-"-
 * 
 * Software distribuido bajo la "GNU GENERAL PUBLIC LICENSE v3", 
 * mas información en /doc/LICENSE
 * 
 * Helper genérico de extranet. Imprime los controles más utilizados.
 * 
 * @category Owl
 * @package Owl
 * @license GNU GPL V3 (http://www.gnu.org/licenses/gpl-3.0.txt)
 * @author Nicolás Daniel Palumbo <npalumbo@xinax.net>
 * @author Aaron Amengual Arranz <aaron.amengual@gmail.com>
 * @version 0.5.4
 * @since 0.3
 * 
 */

class OwlExtranetHelper{

	
	/**
	 * Imprime un campo de texto. Los parámetros opcionales 
	 * sobreescribirán los valores por defecto.
	 * 
	 * @param string $name
	 * @param string $label
	 * @param boolean $required
	 * @param string $css_class
	 * @param string $value
	 * @param string $error
	 * @param string $id
	 * @param string $tooltip
	 * @param string $extra
	 */
	public static function echoTextField($name, $label, $css_class = null, $required = false, $value = null, $error = null, $id = null, $tooltip = null, $extra = null){
		
		// Id
		is_null($id) ? $id = $name : $id;
		
		// Clase
		is_null($css_class) ? $css_class = 't1' : $css_class;
		
		// Value
		!is_null($value) ? $value = 'value="' . $value . '"' : $value = '';
		
		// Error class
		!is_null($error) ? $error_class = ' active' : $error_class = '';

		// Tooltip
		!is_null($tooltip) ? $tooltip_class = ' tooltip' : $tooltip_class = '';
		
		// Extra
		!is_null($extra) ? $extra = ' ' . $extra : $extra = '';
		
		// Required
		$required_class = $required ? ' required' : '';
		
		// Se imprime el campo
		echo '<div class="field' . $required_class . $tooltip_class . '">
			<label for="' . $id . '">' . $label . '</label>
			<input type="text" name="' . $name . '" id="' . $id . '" class="' . $css_class . '" ' . $value . $extra . '  />
			<p class="error_auto' . $error_class . '" id="error' . ucfirst($id) . '">' . $error . '</p>' . 
			( !is_null($tooltip) ? '<a onmouseover="this.childNodes[0].style.display=\'block\'" onmouseout="this.childNodes[0].style.display=\'none\'"><span>' . $tooltip . '</span></a>' : '' ) .
		'</div>';
		
	}
	
	/**
	 * 
	 * Imprime un campo de contraseña
	 * 
	 * @param string $name
	 * @param string $label
	 * @param boolean $required
	 * @param string $css_class
	 * @param string $value
	 * @param string $error
	 * @param string $id
	 * @param string $tooltip
	 * @param string $extra
	 */
	public static function echoPasswordField($name, $label, $css_class = null, $required = false, $value = null, $error = null, $id = null, $tooltip = null, $extra = null){
		
		// Required
		$required_class = $required ? ' required' : '';
		
		// Clase
		is_null($css_class) ? $css_class = 't1' : $css_class;
		
		// Value
		!is_null($value) ? $value = 'value="' . $value . '"' : $value = '';
		
		// Error class
		!is_null($error) ? $error_class = ' active' : $error_class = '';

		// Id
		is_null($id) ? $id = $name : $id;
		
		// Tooltip
		!is_null($tooltip) ? $tooltip_class = ' tooltip' : $tooltip_class = '';
		
		// Extra
		!is_null($extra) ? $extra = ' ' . $extra : $extra = '';
		
		
		// Se imprime el campo
		echo '<div class="field ' . $required_class . $tooltip_class . '">
			<label for="' . $id . '">' . $label . '</label>
			<input type="password" name="' . $name . '" id="' . $id . '" class="' . $css_class . '" ' . $value . $extra . ' />
			<p class="error_auto' . $error_class . '" id="error' . ucfirst($id) . '">' . $error . '</p>' . 
			( !is_null($tooltip) ? '<a onmouseover="this.childNodes[0].style.display=\'block\'" onmouseout="this.childNodes[0].style.display=\'none\'"><span>' . $tooltip . '</span></a>' : '' ) .
		'</div>';		
		
	}
	
	/**
	 * Imprime un campo del tipo textearea. 
	 * 
	 * @param string $name
	 * @param string $label
	 * @param boolean $required
	 * @param string $css_class
	 * @param string $value
	 * @param string $error
	 * @param string $id
	 */
	public static function echoTextareaField($name, $label, $css_class = null, $required = false, $error = null, $value = null, $id = null){

		// Id
		is_null($id) ? $id = $name : $id;
		
		// Clase
		is_null($css_class) ? $css_class = 'ta1' : $css_class;
		
		// Error class
		!is_null($error) ? $error_class = ' active' : $error_class = '';
		
		// Required
		$required_class = $required ? ' required' : '';
		
		echo '<div class="field ' . $required_class . '">
			  	  <label for="' . $id . '">' . $label . '</label>
			  	  <textarea id="' . $id . '" col="80" rows="10" name="' . $name . '" class="' . $css_class . '">' . $value . '</textarea>
			  	  <p class="error_auto' . $error_class . '" id="error' . ucfirst($id) . '">' . $error . '</p>
			  </div>';
		
	}
	
	
	/**
	 * Imprime el código html de control select. Este método
	 * acepta como parámetro dos tipos de arrays ( de DataObjects o de Arrays Bidimensionales).
	 * La clave o método indicada en $keyItem se empleará para los values de los options, 
	 * y la de valueItem para el label de los options.
	 * 
	 * @param string $name
	 * @param string $label
	 * @param array $elements
	 * @param string $keyItem
	 * @param string $valueItem
	 * @param boolean $required
	 * @param string $selectedKey
	 * @param string $error
	 * @param string $id
	 * @param string $defaultItemText
	 * @param string $css_class
	 * @throws OwlException
	 */
	public static function echoSelectField($name, $label, $elements, $keyItem, $valueItem, $css_class = null, $selectedKey = null, $required = false, $error = null, $id = null, $defaultItemText = null){

		// Se comprueba la integridad del array de datos
		if (is_null($elements) || (is_array($elements) && count($elements) == 0)){
			return;
		}
		
		// Required
		$required_class = $required ? ' required' : '';
		
		// Id
		is_null($id) ? $id = $name : $id;
		
		// Clase
		is_null($css_class) ? $css_class = 't1' : $css_class;		
		
		// Error class
		!is_null($error) ? $error_class = ' active' : $error_class = '';

		// Texto por defecto
		is_null($defaultItemText) ? $defaultItemText = '' : $defaultItemText;
		
		// Se determinará el tipo de dato de los elementos a iterar
		if (is_array($elements)){
			$elemento_1 = $elements[0];
		} else {
			$elemento_1 = $elements;
		}

		// Diferentes tipos soportados ( DO | Array )
		if ($elemento_1 instanceof OwlGenericDO){
			if (!method_exists($elemento_1, $keyItem) || !method_exists($elemento_1, $valueItem)){
				throw new OwlException('La colección de elementos (DO) para el el selector, no contiene ninguno de los métodos esperados', 500); 
			}
			$mode = 'do';
		} elseif (is_array($elemento_1)) {
			if (!array_key_exists($keyItem, $elemento_1) || !array_key_exists($valueItem, $elemento_1) ){
				throw new OwlException('La colección de elementos (Array) para el el selector, no contiene ninguna de las claves esperadas', 500);
			}
			$mode = 'arr';
		} else {
			throw new OwlException('No se puede determinar el tipo de objeto a tratar en la iteración.', 500);
		}
		
		// Se imprime el control
		echo '<div class="field ' . $required_class .'">
				<label for="' . $name . '">' . $label . '</label>
				<select name="' . $name . '" class="' . $css_class . '" id="' . $id . '">
					<option value="">' . $defaultItemText . '</option>';
		
					foreach ($elements as $element){
						
						if ('do' == $mode){
							$key = $element->$keyItem();
							$value = $element->$valueItem();
						} else {
							$key = $element[$keyItem];
							$value = $element[$valueItem];
						}
						
						if ($selectedKey == $key){
							$selectedStr = 'selected="selected"';
						} else {
							$selectedStr = '';
						}
						
						echo '<option value="' . $key . '"' . $selectedStr . '>' . $value . '</option>' . "\n";
					}
					
				echo '</select>
					 <p class="error_auto' . $error_class . '" id="error' . ucfirst($id) . '">' . $error . '</p>
			 </div>';
		
	}
	
	/**
	 * 
	 * Imprime el código html de un selector múltiple
	 * @param string $name
	 * @param string $label
	 * @param array $elements
	 * @param string $keyItem
	 * @param string $valueItem
	 * @param boolean $required
	 * @param string $select_class
	 * @param array $selected_keys
	 * @param string $id
	 * @param string $error
	 * @param string $tooltip
	 * @param string $defaultItemText
	 * @param string $extra
	 * @throws OwlException
	 */
	public static function echoMultiselectField($name, $label, $elements, $keyItem, $valueItem, $select_class = null, $required = false, $selected_keys = null, $id = null, $error = null, $tooltip = null, $defaultItemText = null, $extra = null){
		
		// Se comprueba la integridad del array de datos
		if (is_null($elements) || (is_array($elements) && count($elements) == 0)){
			return;
		}
		
		// Required
		$required_class = $required ? ' required' : '';
		
		// Clase
		is_null($select_class) ? $select_class = 'ta1' : $select_class;
		
		// Elementos seleccionados
		is_null($selected_keys) ? $selected_keys = array() : '';
		
		// Id
		is_null($id) ? $id = $name : $id;
		
		// Error class
		!is_null($error) ? $error_class = ' active' : $error_class = '';

		// Tooltip
		!is_null($tooltip) ? $tooltip_class = ' tooltip' : $tooltip_class = '';
		
		// Se determinará el tipo de dato de los elementos a iterar
		if (is_array($elements)){
			$elemento_1 = $elements[0];
		} else {
			$elemento_1 = $elements;
		}

		// Diferentes tipos soportados ( DO | Array )
		if ($elemento_1 instanceof OwlGenericDO){
			if (!method_exists($elemento_1, $keyItem) || !method_exists($elemento_1, $valueItem)){
				throw new OwlException('La colección de elementos (DO) para el el selector, no contiene ninguno de los métodos esperados', 500); 
			}
			$mode = 'do';
		} elseif (is_array($elemento_1)) {
			if (!array_key_exists($keyItem, $elemento_1) || !array_key_exists($valueItem, $elemento_1) ){
				throw new OwlException('La colección de elementos (Array) para el el selector, no contiene ninguna de las claves esperadas', 500);
			}
			$mode = 'arr';
		} else {
			throw new OwlException('No se puede determinar el tipo de objeto a tratar en la iteración.', 500);
		}
		
		echo '<div class="field' . $required_class . $tooltip_class . '">
            <label for="' . $id . '">' . $label .'</label>
            <select name="' . $name .'[]" multiple="multiple" id="' . $id . '" class="' . $select_class . '">';
                echo is_null($defaultItemText) ? '' :  '<option value="">' . $defaultItemText . '</option>';
		
					foreach ($elements as $element){
						
						if ('do' == $mode){
							$key = $element->$keyItem();
							$value = $element->$valueItem();
						} else {
							$key = $element[$keyItem];
							$value = $element[$valueItem];
						}
						
						if ( in_array($key, $selected_keys) ){
							$selectedStr = 'selected="selected"';
						} else {
							$selectedStr = '';
						}
						
						echo '<option value="' . $key . '"' . $selectedStr . '>' . $value . '</option>' . "\n";
					}
                
            echo '</select>
            <p class="error_auto' . $error_class . '" id="error' . ucfirst($id) . '">' . $error . '</p>' . 
			( !is_null($tooltip) ? '<a onmouseover="this.childNodes[0].style.display=\'block\'" onmouseout="this.childNodes[0].style.display=\'none\'"><span>' . $tooltip . '</span></a>' : '' ) .
		'</div>';
	}

	/**
	 * Imprime un campo de archivo. Los parámetros opcionales 
	 * sobreescribirán los valores por defecto.
	 * Para maquetar el tamaño del campo en Firefox usar $size,
	 * en IE usar $css_class
	 * 
	 * @param string $name
	 * @param string $label
	 * @param boolean $required
	 * @param string $size
	 * @param string $class
	 * @param string $error
	 * @param string $id
	 * @param string $tooltip
	 * @param string $extra
	 */
	public static function echoFileField($name, $label, $size = null, $css_class = null, $required = false, $error = null, $id = null, $tooltip = null, $extra = null){
		
		// Id
		is_null($id) ? $id = $name : $id;
		
		// Tamaño
		is_null($size) ? $size = '20' : $size;
		
		// Clase
		$class = is_null($css_class) ? '' : ' class="' . $css_class . '" ';
		
		// Error class
		!is_null($error) ? $error_class = ' active' : $error_class = '';

		// Tooltip
		!is_null($tooltip) ? $tooltip_class = ' tooltip' : $tooltip_class = '';
		
		// Extra
		!is_null($extra) ? $extra = ' ' . $extra : $extra = '';
		
		// Required
		$required_class = $required ? ' required' : '';
		
		// Se imprime el campo
		echo '<div class="field' . $required_class . $tooltip_class . '">
			<label for="' . $id . '">' . $label . '</label>
			<input type="file" name="' . $name . '" id="' . $id . '" size="' . $size . '"'  . $class .  $extra . '  />
			<p class="error_auto' . $error_class . '" id="error' . ucfirst($id) . '">' . $error . '</p>' . 
			( !is_null($tooltip) ? '<a onmouseover="this.childNodes[0].style.display=\'block\'" onmouseout="this.childNodes[0].style.display=\'none\'"><span>' . $tooltip . '</span></a>' : '' ) .
		'</div>';
		
	}
	
	/**
	 * Imprime un botón de submit
	 * 
	 * @param string $value
	 * @param string $fieldClass
	 * @param string $inputClass
	 */
	public static function echoSubmitButton($value, $fieldClass = null, $inputClass = null){
		
		echo '<div class="field ' . $fieldClass . '">
              	 <input type="submit" value="' . $value . '" class="btnSubmit ' . $inputClass .'" />
              </div>';
		
	}
	
	/**
	 * 
	 * Imprime un campo checkbox
	 * @param string $name
	 * @param string $label
	 * @param string $value
	 * @param boolean $is_checked
	 * @param string $input_class
	 * @param string $label_class
	 * @param string $id
	 * @param string $extra
	 */
	public static function echoCheckbox($name, $label, $is_checked = false, $input_class = null, $label_class = null, $id = null, $value = null, $extra = null){

		// Checked
		$checked = ($is_checked) ? 'checked="checked"' : ''; 
		
		// Clase input
		is_null($input_class) ? $input_class = '' : $input_class;

		// Clase label
		is_null($label_class) ? $label_class = 'alter' : $label_class;
		
		// Id
		is_null($id) ? $id = $name : $id;
		
		// Value
		!is_null($value) ? $value = 'value="' . $value . '" ' : $value = '';
		
		// Extra
		!is_null($extra) ? $extra = ' ' . $extra : $extra = '';
		
		echo '<div class="field checkbox">
            <label for="' . $id . '" class="' . $label_class . '">' . $label . '</label>
            <input type="checkbox" name="' . $name . '" ' . $value . 'id="' . $id . '" class="' . $input_class . '" ' . $checked . ' />
        </div>';
	}
	
	/**
	 * Imprime un div separador
	 * @param string $extra_class
	 */
	public static function echoSeparator($extra_class = null){
		
		// Clase extra
		!is_null($extra_class) ? $extra_class = ' ' . $extra_class : $extra_class = '';
		
		echo '<div class="separadorH' . $extra_class . '"></div>';
		
	}
	
	/**
	 * Imprime el título de una sección
	 * @param string $titulo
	 */
	public static function echoSeccion($titulo){
		
		echo '<h3 class="seccion">' . $titulo . '</h3>';
		
	}
	
}

?>