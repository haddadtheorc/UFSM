import React, { useState } from "react";
import CheckBox from "../Filters/CheckBox";
import Card from "../UI/Card";
import GeneralChart from "./GeneralChart/GeneralChart";
import GeneralChart2 from "./GeneralChart/GeneralChart2";
import IfeRequest from "./RequestsChart/IfeRequest";
import AreasChart from "./AreasChart/AreasChart";
import AreasByIfe from "./AreasChart/AreasByIfe";
import StudentsChart from "./StudentsChart/StudentsChart";
import PopularDisciplines from "./DisciplinesChart/PopularDisciplines";
import RequestsChart from "./RequestsChart/RequestsChart";
import GeneralChartByIfe from "./GeneralChart/GeneralChartByIfe";
import RequestsByIfe from "./RequestsChart/RequestsByIfe";

const Charts = (props) => {
  const [filteredIFE, setFilteredIFE] = useState(props.data);

  const handleAllChecked = (event) => {
    props.data.forEach((data) => (data.isChecked = event.target.checked));
    setFilteredIFE(props.data.filter((data) => data.isChecked === true));
  };

  const handleCheckChieldElement = (event) => {
    props.data.forEach((data) => {
      if (data.name === event.target.value)
        data.isChecked = event.target.checked;
    });
    setFilteredIFE(props.data.filter((data) => data.isChecked === true));
  };

  return (
    <div>
      <center>
        <h1>Relatório PROMOVER</h1>
      </center>
      <input type="checkbox" onClick={handleAllChecked} value="checkedall" />
      Check / Uncheck All
      <ul>
        {props.data.map((data) => {
          return (
            <CheckBox
              handleCheckChieldElement={handleCheckChieldElement}
              {...data}
            />
          );
        })}
      </ul>
      <Card>
        <GeneralChart data={filteredIFE} />
        <GeneralChart2 data={filteredIFE} />
      </Card>
      <Card>
        <GeneralChartByIfe
          data={props.data}
          onChangeFilter={props.onChangeFilter}
        />
      </Card>
      <Card>
        <AreasChart data={filteredIFE} />
      </Card>
      <Card>
        <AreasByIfe data={props.data} onChangeFilter={props.onChangeFilter} />
      </Card>
      <Card>
        <StudentsChart data={filteredIFE} disciplines={props.disciplines} />
      </Card>
      <Card>
        <PopularDisciplines data={filteredIFE} />
      </Card>
      <Card>
        <IfeRequest data={props.data} />
      </Card>
      <Card>
        <RequestsChart data={filteredIFE} />
      </Card>
      <RequestsByIfe data={props.data} onChangeFilter={props.onChangeFilter} />
    </div>
  );
};

export default Charts;
