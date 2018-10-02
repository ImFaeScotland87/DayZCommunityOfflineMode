class ObjectInfoMenu extends PopupMenu 
{

	static EditBoxWidget infoPosX;
	static EditBoxWidget infoPosY;
	static EditBoxWidget infoPosZ;

	static EditBoxWidget infoPosYaw;
	static EditBoxWidget infoPosPitch;
	static EditBoxWidget infoPosRoll;

	void ObjectInfoMenu()
	{

	}

	void ~ObjectInfoMenu() 
	{
		GetGame().GetCallQueue( CALL_CATEGORY_GUI ).Remove( Update );
	}

	override void Init( ) 
	{
		infoPosX = layoutRoot.FindAnyWidget( "object_info_pos_x" );
		infoPosY = layoutRoot.FindAnyWidget( "object_info_pos_y" );
		infoPosZ = layoutRoot.FindAnyWidget( "object_info_pos_z" );
		infoPosYaw = layoutRoot.FindAnyWidget( "object_info_yaw_input" );
		infoPosPitch = layoutRoot.FindAnyWidget( "object_info_pitch_input" );
		infoPosRoll = layoutRoot.FindAnyWidget( "object_info_roll_input" );
	}

	override bool OnMouseWheel(Widget w, int x, int y, int wheel)
	{

		if ( !GetSelectedObject() ) 
		{
			return false;
		}
		vector orientation = GetSelectedObject().GetOrientation();
		vector position = GetSelectedObject().GetPosition();

		bool up = wheel < 0;
		int value = 1;

		if ( up ) value = -1;

		if ( w == infoPosYaw ) 
		{
			orientation[0] = orientation[0] + value;
			GetSelectedObject().SetOrientation( orientation );
			infoPosYaw.SetText( orientation[0].ToString() );
		}
		if ( w == infoPosPitch ) 
		{
			if ( orientation[0] > 0 ) // seemless pitch change
			{
				value = -value;
			}
			orientation[1] = orientation[1] + value;
			GetSelectedObject().SetOrientation( orientation );
			infoPosPitch.SetText( orientation[1].ToString() );

		}
		if ( w == infoPosRoll ) 
		{
			orientation[2] = orientation[2] + value;
			GetSelectedObject().SetOrientation( orientation );
			infoPosRoll.SetText( orientation[2].ToString() );
		}
		if ( w == infoPosY ) 
		{
			position[1] = position[1] + value * 0.05;
			GetSelectedObject().SetPosition( position );
			ForceTargetCollisionUpdate( GetSelectedObject() );
			infoPosY.SetText( position[1].ToString() );
		}
		if ( w == infoPosX ) 
		{
			position[0] = position[0] + value * 0.05;
			GetSelectedObject().SetPosition( position );
			ForceTargetCollisionUpdate( GetSelectedObject() );
			infoPosX.SetText( position[0].ToString() );
		}
		if ( w == infoPosZ ) 
		{
			position[2] = position[2] + value * 0.05;
			GetSelectedObject().SetPosition( position );
			ForceTargetCollisionUpdate( GetSelectedObject() );
			infoPosZ.SetText( position[2].ToString() );
		}

		return false;
	}

	override bool OnChange( Widget w, int x, int y, bool finished ) // finished = press enter
	{
		if ( !w.IsInherited( EditBoxWidget )) 
		{
			return false;
		}

		vector pos = GetSelectedObject().GetPosition();
		vector orientation = GetSelectedObject().GetOrientation();

		EditBoxWidget editWidget = w;
		string text = editWidget.GetText();

		float value = text.ToFloat();

		if ( editWidget == infoPosYaw ) 
		{
			orientation[0] = value;
		}
		if ( editWidget == infoPosPitch ) 
		{
			orientation[1] = value;
		}
		if ( editWidget == infoPosRoll ) 
		{
			orientation[1] = value;
		}
		if ( editWidget == infoPosX ) 
		{
			pos[0] = value;
		}
		if ( editWidget == infoPosY ) 
		{
			pos[1] = value;
		}
		if ( editWidget == infoPosZ ) 
		{
			pos[2] = value;
		}
		GetSelectedObject().SetPosition( pos );
		GetSelectedObject().SetOrientation( orientation );

/*
		bool check = false; //?????????????

        if ( editWidget == infoPosPitch )
        {
        	for(int i = 0; i < text.Length(); i++ ) 
        	{
        		string token;
        		string character = text.Get(i);
        		int result = character.ParseStringEx(token);

        		if ( result == 4 || text.Get(i) == "." ) 
        		{
        			newText = newText + token;
        			check = true; // lol wtf why this crashing. come back to this
        		}
        	}

        	if ( check ) // idk why this bool is causing unknown module crash
        	{
        		orientation[1] = newText.ToFloat();
        		GetSelectedObject().SetOrientation(orientation);
        	}
        	else 
        	{
        		editWidget.SetText( newText );
        	}
        	
            return false;
        }

        */

        return false;
    }

    override bool OnMouseEnter(Widget w, int x, int y)
	{
		return false;
	}
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		SetFocus( layoutRoot );
		return false;
	}

    override void OnShow() 
    {
    	GetGame().GetCallQueue( CALL_CATEGORY_GUI ).CallLater( Update, 500, true );
    }

    override void OnHide() 
    {
    	//GetGame().GetUpdateQueue( CALL_CATEGORY_GUI ).Remove( Update );
    }

	void Update() 
	{
		Object selectedObject = GetSelectedObject();
		string text = "No object selected"
		TStringArray paths = new TStringArray;

		bool selected = false;

		Widget focusedWidget = GetFocus();

		if ( selectedObject ) 
		{
			infoPosX.ClearFlags( WidgetFlags.IGNOREPOINTER );
			infoPosY.ClearFlags( WidgetFlags.IGNOREPOINTER );
			infoPosZ.ClearFlags( WidgetFlags.IGNOREPOINTER );
			infoPosYaw.ClearFlags( WidgetFlags.IGNOREPOINTER );
			infoPosPitch.ClearFlags( WidgetFlags.IGNOREPOINTER );
			infoPosRoll.ClearFlags( WidgetFlags.IGNOREPOINTER );

			text = selectedObject.GetType();
		} else 
		{
			infoPosX.SetFlags( WidgetFlags.IGNOREPOINTER );
			infoPosY.SetFlags( WidgetFlags.IGNOREPOINTER );
			infoPosZ.SetFlags( WidgetFlags.IGNOREPOINTER );
			infoPosYaw.SetFlags( WidgetFlags.IGNOREPOINTER );
			infoPosPitch.SetFlags( WidgetFlags.IGNOREPOINTER );
			infoPosRoll.SetFlags( WidgetFlags.IGNOREPOINTER );
		}

		TextWidget selectedObjectWidget = layoutRoot.FindAnyWidget( "object_editor_info_select_input" );
		selectedObjectWidget.SetText( text );

		// SetFlags(int flags, bool immedUpdate = true);
	}

	Object GetSelectedObject() 
	{
		return ObjectEditor.Cast(GetModuleManager().GetModule( ObjectEditor )).m_SelectedObject;
	}
}