int getCommandStatusId(Tlist* command, Tlist* first_param, Tlist *second_param, int error_code){
	int id = getCommandId(command, first_param, second_param, error_code);

	if(id == error_code){
		return error_code;
	}

	if(second_param == NULL){
		/* DECLARE / REMOVE / VALID / ENERGY_ONE_PARAM */
		if(id == ENERGY_ID && !isHistoryValid(first_param)){
			return error_code;
		}
	}
	else{
		/* ENERGY_TWO_PARAMS / EQUAL */
		if(id == ENERGY_ID){
		}
	}
}


int main(){

	while((input_status = getInput(command, first_param, second_param)) != EOF){

		command_status_id = getCommandStatusId(command, first_param, second_param);

		switch(command_status_id){
			case DECLARE: {
				historyDeclare(first_param);
			}
			case REMOVE: {
				historyRemove(first_param);
			}
			case VALID: {
				if(historyValid(first_param)){
					say_YES
				}
				else{
					say_NO
				}
			}
			case ENERGY: {
				setEnergy(first_param);
			}
			case EQUAL: {
				
			}
			default: {
				say_error
			}
		}

		deleteList(&command);
		deleteList(&first_param);
		deleteList(&second_param);

	}

	return 0;
}