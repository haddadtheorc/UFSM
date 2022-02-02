import React from "react";
import Chart from "react-apexcharts";

const RequestsChart = (props) => {
  let data_name = props.data.map((data) => data.name);
  let data_requests_total = props.data.map((data) => data.requests_total);
  let data_requests_approved = props.data.map((data) => data.requests_approved);

  let state = {
    options: {
      colors: ["#9966ff", "#4bc0c0", "#1a98ed", "#fa2f5a", "#6e7075"],
      chart: {
        type: "bar",
        height: 350,
        stacked: false,
        toolbar: {
          show: true,
        },
        zoom: {
          enabled: true,
        },
      },
      responsive: [
        {
          breakpoint: 480,
          options: {
            legend: {
              position: "bottom",
              offsetX: 10,
              offsetY: 0,
            },
          },
        },
      ],
      plotOptions: {
        bar: {
          horizontal: false,
          endingShape: "rounded",
        },
      },
      xaxis: {
        type: "category",
        categories: data_name,
        labels: {
          style: {
            fontWeight: 1000,
          },
        },
      },
      legend: {
        position: "right",
        offsetY: 40,
      },
      fill: {
        opacity: 1,
      },
    },
    series: [
      {
        name: "Solicitações Recebidas",
        data: data_requests_total,
      },
      {
        name: "Solicitações Aprovadas",
        data: data_requests_approved,
      },
    ],
  };

  return (
    <div id="chart">
      <center>
        <h2>4.? Solicitações</h2>
      </center>
      <Chart
        options={state.options}
        series={state.series}
        type="bar"
        height={500}
      />
    </div>
  );
};

export default RequestsChart;
