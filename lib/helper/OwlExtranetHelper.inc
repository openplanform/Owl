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
 * @version 0.5.4
 * @since 0.3
 * 
 */

class OwlExtranetHelper{

	
	/**
	 * Imprime un campo de texto. Los parámetros opcionales 
	 * sobreescribiran los valores por defecto.
	 * 
	 * @param string $name
	 * @param string $label
	 * @param boolean $required
	 * @param string $class
	 * @param string $value
	 * @param string $error
	 * @param string $id
	 */
	public static function echoTextField($name, $label, $required = false, $css_class = null, $value = null, $error = null, $id = null){
		
		// Id
		is_null($id) ? $id = $name : $id;
		
		// Clase
		is_null($css_class) ? $css_class = 't1' : $css_class;
		
		// Value
		!is_null($value) ? $value = 'value="' . $value . '"' : $value = '';
		
		// Error class
		!is_null($error) ? $errorClass = ' active' : $errorClass = '';
		
		// Required
		$reqStr = $required ? ' required' : '';
		
		// Se imprime el campo
		echo '<div class="field ' . $reqStr . '">
			<label for="' . $id . '">' . $label . '</label>
			<input type="text" name="' . $name . '" id="' . $id . '" class="' . $css_class . '" ' . $value . ' />
			<p class="error_auto' . $errorClass . '" id="error' . $id . '">' . $error . '</p>
		</div>';
		
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
	 */
	public static function echoPasswordField($name, $label, $required = false, $css_class = null, $value = null, $error = null, $id = null){
		
		// Id
		is_null($id) ? $id = $name : $id;
		
		// Clase
		is_null($css_class) ? $css_class = 't1' : $css_class;
		
		// Value
		!is_null($value) ? $value = 'value="' . $value . '"' : $value = '';
		
		// Error class
		!is_null($error) ? $errorClass = ' active' : $errorClass = '';
		
		// Required
		$reqStr = $required ? ' required' : '';
		
		// Se imprime el campo
		echo '<div class="field ' . $reqStr . '">
			<label for="' . $id . '">' . $label . '</label>
			<input type="password" name="' . $name . '" id="' . $id . '" class="' . $css_class . '" ' . $value . ' />
			<p class="error_auto' . $errorClass . '" id="error' . $id . '">' . $error . '</p>
		</div>';		
		
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
	public static function echoTextareaField($name, $label, $required = false, $css_class = null, $value = null, $error = null, $id = null){

		// Id
		is_null($id) ? $id = $name : $id;
		
		// Clase
		is_null($css_class) ? $css_class = 'ta1' : $css_class;
		
		// Error class
		!is_null($error) ? $errorClass = ' active' : $errorClass = '';
		
		// Required
		$reqStr = $required ? ' required' : '';
		
		echo '<div class="field ' . $reqStr . '">
			  	  <label for="' . $id . '">' . $label . '</label>
			  	  <textarea id="' . $id . '" col="80" rows="10" name="' . $name . '" class="' . $css_class . '">' . $value . '</textarea>
			  	  <p class="error_auto' . $errorClass . '" id="error' . $id . '">' . $error . '</p>
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
	public static function echoSelectField($name, $label, $elements, $keyItem, $valueItem, $required = false, $selectedKey = null, $error = null, $id = null, $defaultItemText = null, $css_class = null){

		// Se comprueba la integridad del array de datos
		if (is_null($elements) || (is_array($elements) && count($elements) == 0)){
			return;
		}
		
		// Required
		$reqStr = $required ? ' required' : '';
		
		// Id
		is_null($id) ? $id = $name : $id;
		
		// Clase
		is_null($css_class) ? $css_class = 't1' : $css_class;		
		
		// Error class
		!is_null($error) ? $errorClass = ' active' : $errorClass = '';

		// Texto por defecto
		is_null($defaultItemText) ? $defaultItemText = '' : $defaultItemText;
		
		// Se determinará el tipo de dato de los elementos a iterar
		if (is_array($elements)){
			$elemento_1 = array_shift($elements);
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
			throw new OwlException('No se puede determinar del tipo de objeto a tratar en la iteración.', 500);
		}
		
		// Se imprime el control
		echo '<div class="field ' . $reqStr .'">
				<label for="' . $name . '">' . $label . '</label>
				<select name="' . $name . '" class="' . $css_class . '">
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
					 <p class="error_auto' . $errorClass . '" id="error' . $id . '">' . $error . '</p>
			 </div>';
		
	}
	
	
	/**
	 * Imprime un botón de submit
	 * 
	 * @param string $value
	 * @param string $fieldClass
	 * @param string $inputClass
	 */
	public static function echoSubmitButton($value, $fieldClass = null, $inputClass = null){
		
		echo '<div class="campo ' . $fieldClass . '">
              	 <input type="submit" value="' . $value . '" class="btnSubmit ' . $inputClass .'" />
              </div>';
		
	}
	
	
	public static function echoMultiselectField(){
		
		
		
	}
	
}

?>