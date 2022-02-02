import React from "react";
// import "./IFE_Filter.css";

const Filter = (props) => {
  const dropdownChangeHandler = (event) => {
    props.onChangeFilter(event.target.value);
  };
  let ifes_list =
    props.data.length > 0 &&
    props.data.map((item, i) => {
      return (
        <option key={i} value={item.name}>
          {item.name}
        </option>
      );
    }, this);

  return (
    <div className="ife_filter">
      <div className="ife_filter__control">
        <label> - </label>
        <select value={props.selected} onChange={dropdownChangeHandler}>
          {ifes_list}
        </select>
      </div>
    </div>
  );
};

export default Filter;
