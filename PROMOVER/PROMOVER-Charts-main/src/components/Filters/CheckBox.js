import React from "react";

const CheckBox = (props) => {
  return (
    <div>
      <input
        type="checkbox"
        key={props.name}
        onClick={props.handleCheckChieldElement}
        value={props.name}
      />
      {props.name}
    </div>
  );
};

export default CheckBox;
